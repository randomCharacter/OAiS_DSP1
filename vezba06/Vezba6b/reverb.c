#include "tistdtypes.h"

/* Max delay */
#define MAX_DELAY 8191
static Int16 reverb_buffer[MAX_DELAY+1]; /* Buffer for maximum of 0.5s delay */
static Int16 reverb_gain;

static Int16 rbuff_read_index;
static Int16 rbuff_write_index;

static void clear_reverb_buffer()
{
	Int16 i;

	for (i = 0; i <= MAX_DELAY; i++)
	{
		reverb_buffer[i] = 0;
	}
}

void simple_reverb_init(Int16 N, Int16 gain)
{
	clear_reverb_buffer();
	rbuff_read_index = 0;
	rbuff_write_index = N;
	reverb_gain = gain;
}

Int16 simple_reverb(Int16 input)
{
	Int16 return_value;

	/* Your code here */

	return return_value;
}

