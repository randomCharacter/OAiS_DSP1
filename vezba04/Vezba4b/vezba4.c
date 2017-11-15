#include <math.h>
#include "tistdtypes.h"


Int16 clipB(Int16 input, Uint16 B)
{
	Int16 max = (1L << (B-1)) - 1;
	Int16 min = - max;
	Int16 output = input;
	if(output > max)
		output = max;
	else if (output < min)
		output = min;

	return output;
}

Int16 wrapAroundB(Int16 input, Uint16 B)
{
		Uint16 mask = (1L << (B)) - 1;
		return input & mask;
}
