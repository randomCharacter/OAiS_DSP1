
#include "adaptive_filter.h"
#include "fir.h"

void lms(Int16 error, Int16 *coeffs, Int16 *history, Uint16 n_coeff, Uint16 *p_state, Int16 lambda)
{
	Int32 accum;
	Int16 lambda_error, x, i;
	Int16 state = *p_state;

	lambda_error = _smpy(lambda, error);

	for (i = n_coeff - 1; i >= 0; i--)
	{
		x = history[state];
		if (++state >= n_coeff) /* incr state and check for wrap */
		{
			state = 0;
		}

		accum = coeffs[i];
		accum += _smpy(lambda_error, x);

		if(accum > 32767)
			coeffs[i] = 32767;
		else if(accum < -32768)
			coeffs[i] = -32768;
		else
			coeffs[i] = (Int16)accum;
	}
}

void nlms(Int16 error, Int16 *coeffs, Int16 *history, Uint16 n_coeff, Uint16 *p_state, Int16 lambda)
{
	/* Your code here */
}

Int16 lms_filter(Int16 x, Int16 d, Int16 *coeffs, Int16 *history, Uint16 n_coeff, Uint16 *p_state, Int16 lambda)
{
	Int16 y, error;

	y = fir_circular(x, coeffs, history, n_coeff, p_state);

	error = d - y;
	lms(error, coeffs, history, n_coeff, p_state, lambda);

    return error;
}

