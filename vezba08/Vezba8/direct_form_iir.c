#include "tistdtypes.h"
#include "direct_form_iir.h"

Int16 iir_basic(Int16 input, Int16* a_coeffs, Int16* x_history, Uint16 n_a_coeff, Int16* b_coeffs,
				Int16* y_history, Uint16 n_b_coeff)
{
    Int16 i;
    Int32 ret_val;
    
	/* shift delay line */
	for (i = n_a_coeff - 2; i >= 0; i--)
	{
		x_history[i + 1] = x_history[i];
	}

	for (i = n_b_coeff - 2; i >= 0; i--)
	{
		y_history[i + 1] = y_history[i];
	}

	/* store input at the beginning of the delay line */
	x_history[0] = input;

	/* calc IIR */
	ret_val = 0;
	for (i = 0; i < n_a_coeff; i++)
	{
		ret_val = _smac(ret_val, a_coeffs[i], x_history[i]);
	}

	ret_val = (ret_val >> 15) * b_coeffs[0];

	for (i = 1; i < n_b_coeff; i++)
	{
		ret_val = _smas(ret_val, b_coeffs[i], y_history[i]);
	}

	y_history[0] = (Int16)(ret_val >> 16);
	return y_history[0];
}


Int16 iir_circular(Int16 input, Int16* a_coeffs, Int16* x_history, Uint16* x_state, Uint16 n_a_coeff, Int16* b_coeffs,
		Int16* y_history, Uint16* y_state, Uint16 n_b_coeff)
{
	int i, x_state_l, y_state_l;
    Int32 ret_val;

    x_state_l = *x_state;               /* copy the filter's state to a local */
    y_state_l = *y_state;
    

	/* store input at the beginning of the delay line */
    x_history[x_state_l] = input;
	/* incr state and check for wrap */
	if (++x_state_l >= n_a_coeff)
	{
		x_state_l = 0;
	}

	/* calc IIR and shift data */
	ret_val = 0;
	for (i = n_a_coeff - 1; i >= 0; i--)
	{
		ret_val = _smac(ret_val, a_coeffs[i], x_history[x_state_l]);
		if (++x_state_l >= n_a_coeff)  /* incr state and check for wrap */
		{
			x_state_l = 0;
		}
	}

	ret_val = (ret_val >> 15) * b_coeffs[0];

	for (i = n_b_coeff - 1; i >= 1; i--)
	{
		if (++y_state_l >= n_b_coeff)
		{
			y_state_l = 0;
		}
		ret_val = _smas(ret_val, b_coeffs[i], y_history[y_state_l]);
	}

	if (++y_state_l >= n_b_coeff)
	{
		y_state_l = 0;
	}

	y_history[y_state_l] = (Int16)(ret_val >> 16);

	if (++y_state_l >= n_b_coeff)
	{
		y_state_l = 0;
	}
    
    *x_state = x_state_l;               /* return new state to caller */
	*y_state = y_state_l;

    return  (Int16)(ret_val >> 16);
}
