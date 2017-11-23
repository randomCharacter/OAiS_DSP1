#include "tistdtypes.h"
#include <math.h>
#include "sine.h"

static Int16 min_delay = 0;
static Int16 max_delay = 0;
static Int16 center_tap = 0;
Uint16 ph = 0;
Int16 delay_mem[4096];

Int16 delay_mem_i = 0;

#define BUFFER_SIZE 512
#define MAX_DELAY BUFFER_SIZE-1
static Int16 current_delay = 0;
static Int16 delay_buffer[BUFFER_SIZE];

static Int16 dbuff_read_index;
static Int16 dbuff_write_index;

static void clear_delay_buffer(void)
{
	Int16 i;

	for (i = 0; i < BUFFER_SIZE; i++)
	{
		delay_buffer[i] = 0;
	}
}

void flanging_init(Int16 min_d, Int16 max_d)
{
	current_delay = min_d;
	clear_delay_buffer();
	dbuff_read_index = 0;
	dbuff_write_index = current_delay;
	min_delay = min_d;
	max_delay = max_d;
	center_tap = min_delay + (max_delay-min_delay)>>1;
}

void update_current_delay(Uint16 f)
{
	Int16 tmp = cos_LT(ph);

	ph+=f;

	current_delay = center_tap - _smpy(center_tap, tmp);

	/*delay_mem[delay_mem_i] = current_delay;
	delay_mem_i++;
	delay_mem_i = delay_mem_i & 4095;
*/
	/*if(delay_dirrection > 0)
	{
		current_delay += delay_step;
		if(current_delay >= max_delay)
		{
			current_delay = max_delay;
			delay_dirrection = -1;
		}
	}
	else if (delay_dirrection < 0)
	{
		current_delay -= delay_step;
		if(current_delay <= min_delay)
		{
			current_delay = min_delay;
			delay_dirrection = 1;
		}
	}*/
	dbuff_read_index = (dbuff_write_index + BUFFER_SIZE - current_delay) & MAX_DELAY;
}

Int16 flanging(Int16 input)
{
	Int16 return_value = input>>1;
	delay_buffer[dbuff_write_index] = return_value;
	dbuff_write_index++; dbuff_write_index = dbuff_write_index & MAX_DELAY;

	return_value += delay_buffer[dbuff_read_index];
	dbuff_read_index++; dbuff_read_index = dbuff_read_index & MAX_DELAY;

	update_current_delay(2);

	return return_value;

}
