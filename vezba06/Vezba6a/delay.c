#include "tistdtypes.h"

/* Max delay */
#define BUFFER_SIZE 16384
#define MAX_DELAY BUFFER_SIZE-1
static Uint32 current_delay = MAX_DELAY;
static Int16 delay_buffer[BUFFER_SIZE];

static Int16 dbuff_read_index;
static Int16 dbuff_write_index;

void clear_delay_buffer(void)
{
	Int16 i;
 
	for (i = 0; i < BUFFER_SIZE; i++)
	{
		delay_buffer[i] = 0;
	}
}

void delay_init(Int16 N)
{
	clear_delay_buffer();
	current_delay = N;
	dbuff_read_index = 0;
	dbuff_write_index = current_delay;
}

void set_current_delay(Int16 N)
{
	dbuff_read_index = (dbuff_write_index + BUFFER_SIZE - N) & MAX_DELAY;
	current_delay = N;
}

Int16 delay(Int16 input)
{
	Int16 return_value;
	delay_buffer[dbuff_write_index] = input;
    dbuff_write_index++; dbuff_write_index = dbuff_write_index & MAX_DELAY;
    return_value = delay_buffer[dbuff_read_index];
    dbuff_read_index++; dbuff_read_index = dbuff_read_index & MAX_DELAY;
    return return_value;
}


