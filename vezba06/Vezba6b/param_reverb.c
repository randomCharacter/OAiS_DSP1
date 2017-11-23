#include "tistdtypes.h"
#include "param_reverb.h"

static void clear_reverb_buffer(Int16* buffer, Int16 buf_size)
{
	Int16 i;

	for (i = 0; i < buf_size; i++)
	{
		buffer[i] = 0;
	}
}

void param_reverb_init(Int16* buffer, Int16 buf_size, Int16* read_index, Int16* write_index, Int16 N)
{
	clear_reverb_buffer(buffer, buf_size);
	*read_index = 0;
	*write_index = N;
}

Int16 param_reverb(Int16 input, Int16* reverb_buffer, Int16 buf_size, Int16* p_read_index, Int16* p_write_index, Int16 gain)
{
	Int16 return_value;
    /* Your code here */
	return return_value;
}


