#include "tistdtypes.h"
#include "echo.h"
#include "delay.h"

static Int16 current_gain = 0;

void echo_init(Int16 N, Int16 gain)
{
	delay_init(N);
	current_gain = gain;
}


Int16 echo(Int16 input)
{
	Int16 delayed_input = delay(input);
	Int16 return_value = _smpy(delayed_input, current_gain);
	return_value += input;
	return  return_value;
}
