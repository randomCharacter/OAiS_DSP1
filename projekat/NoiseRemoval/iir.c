#include "iir.h"

/**************************************
 * IIR filtar prvog reda
 *
 * input - ulazni odbirak
 * coefficients - koeficijenti [a0 a1 b0 b1]
 * z_x - memorija za ulazne odbirke (niz duzine 2)
 * z_y - memorija za izlazne odbirke (niz duzine 2)
 *
 * povratna vrednost - izlazni odbirak
 *
 **************************************/

Int16 first_order_IIR(Int16 input, Int16* coefficients, Int16* z_x, Int16* z_y) {
	Int32 temp;

	z_x[0] = input; /* Copy input to x[0] */

	temp = ((Int32) coefficients[0] * z_x[0]); /* B0 * x(n)     */
	temp += ((Int32) coefficients[1] * z_x[1]); /* B1 * x(n-1) */
	temp -= ((Int32) coefficients[3] * z_y[1]); /* A1 * y(n-1) */

	/* Divide temp by coefficients[A0] to remove fractional part */
	temp >>= 15;

	z_y[0] = (Int16) (temp);

	/* Range limit temp between maximum and minimum */

	if (temp > 32767) {
		temp = 32767;
	} else if (temp < -32767) {
		temp = -32767;
	}

	/* Shuffle values along one place for next time */

	z_y[1] = z_y[0]; /* y(n-1) = y(n)   */
	z_x[1] = z_x[0]; /* x(n-1) = x(n)   */

	return ((Int16) temp);
}

/**************************************
 * IIR filtar drugog reda
 *
 * input - ulazni odbirak
 * coefficients - koeficijenti [a0 a1/2 a2 b0 b1/2 b2]
 * z_x - memorija za ulazne odbirke (niz duzine 2)
 * z_y - memorija za izlazne odbirke (niz duzine 2)
 *
 * povratna vrednost - izlazni odbirak
 *
 * NAPOMENA: Koeficijenti b1 i a1 se nalaze u opsegu [-2, 2),
 * stoga se prosledjuje polovina njihove vrednosti kako bi
 * mogli biti prezentovani u 1.31 prezentaciji brojeva u
 * nepokretnom zarezu
 *************************************/

Int16 second_order_IIR(Int16 input, Int16* coefficients, Int16* x_history, Int16* y_history) {
    Int32 accum = 0;

    accum = _smac(accum, coefficients[0], input);        /* A0 * x(n)     */
    accum = _smac(accum, coefficients[1], x_history[0]); /* A1/2 * x(n-1) */
    accum = _smac(accum, coefficients[1], x_history[0]); /* A1/2 * x(n-1) */
    accum = _smac(accum, coefficients[2], x_history[1]); /* A2 * x(n-2)   */
    accum = _smas(accum, coefficients[4], y_history[0]); /* B1/2 * y(n-1) */
    accum = _smas(accum, coefficients[4], y_history[0]); /* B1/2 * y(n-1) */
    accum = _smas(accum, coefficients[5], y_history[1]); /* B2 * y(n-2)   */

    accum >>= 16;

    y_history[1] = y_history[0];    /* y(n-2) = y(n-1) */
    y_history[0] = (Int16) (accum); /* y(n-1) = y(n)   */
    x_history [1] = x_history [0];  /* x(n-2) = x(n-1) */
    x_history [0] = input;          /* x(n-1) = x(n)   */

    return ((Int16) accum);
}



Int16 fourth_order_IIR(Int16 input, Int16 coefficients[][6], Int16 x_history[][2],
		Int16 y_history[][2]) {
	Uint32 accum;
	Int16 temp;
	Uint16 stage;

    temp = input; /* Copy input to temp */

	for ( stage = 0 ; stage < 2 ; stage++) /* for two stages */
	{
		accum = 0;
		accum = _smac(accum, coefficients[stage][0], temp);         /* A0 * x(n)     */
		accum = _smac(accum, coefficients[stage][1], x_history[stage][0]); /* A1/2 * x(n-1) */
		accum = _smac(accum, coefficients[stage][1], x_history[stage][0]); /* A1/2 * x(n-1) */
		accum = _smac(accum, coefficients[stage][2], x_history[stage][1]); /* A2 * x(n-2)   */
		accum = _smas(accum, coefficients[stage][4], y_history[stage][0]); /* B1/2 * y(n-1) */
		accum = _smas(accum, coefficients[stage][4], y_history[stage][0]); /* B1/2 * y(n-1) */
		accum = _smas(accum, coefficients[stage][5], y_history[stage][1]); /* B2 * y(n-2)   */

		accum >>= 16;

		/* Shuffle values along one place for next time */
		y_history[stage][1] = y_history[stage][0];    /* y(n-2) = y(n-1) */
		y_history[stage][0] = (Int16) (accum); /* y(n-1) = y(n)   */
		x_history[stage][1] = x_history[stage][0];  /* x(n-2) = x(n-1) */
		x_history[stage][0] = temp;          /* x(n-1) = x(n)   */

		/* temp is used as input next time through */
		temp = (Int16)accum;
	}
	/* End loop */

	return (Int16)accum;
}


Int16 Nth_order_IIR(Int16 input, Int16 coefficients[][6], Int16 x_history[][2], Int16 y_history[][2], Int16 order) {
		Uint32 accum;
		Int32 temp;
		Uint16 stage;

		/* Copy input to temp */
		temp = input;

		/* for N stages */
	    for (stage = 0; stage < order; stage++) {
	    	accum = 0;
				/* A0 * x(n)      (x(n) is in temp)     */
	    	accum = _smac(accum, coefficients[stage][0], temp);

				/* A1/2 * x(n-1)  (x(n-1) is in x_historty[stage][0] */
	    	accum = _smac(accum, coefficients[stage][1], x_history[stage][0]);
				/* A1/2 * x(n-1) */
	    	accum = _smac(accum, coefficients[stage][1], x_history[stage][0]);
				/* A2 * x(n-2)   */
	    	accum = _smac(accum, coefficients[stage][2], x_history[stage][1]);
				/* B1/2 * y(n-1) (y(n-1) is in y_historty[stage][0]*/
	    	accum = _smas(accum, coefficients[stage][4], y_history[stage][0]);
				/* B1/2 * y(n-1) */
	    	accum = _smas(accum, coefficients[stage][4], y_history[stage][0]);
				/* B2 * y(n-2)   */
	    	accum = _smas(accum, coefficients[stage][5], y_history[stage][1]);
			/* Divide temp by 2^15 to remove fractional part */
			accum >>= 16;
			/* Range limit temp between maximum and minimum */

			/* Shuffle values along one place for next time */

			y_history[stage][1] = y_history[stage][0];/* y(n-2) = y(n-1) */
			y_history[stage][0] = (Int16) (accum);	/* y(n-1) = y(n)   */

			x_history[stage][1] = x_history[stage][0];	/* x(n-2) = x(n-1) */
			x_history[stage][0] = temp;  	/* x(n-1) = x(n)   */

			/* temp is used as input next time through */
	    	temp = accum;
		/* End loop */
	    }

	    return (Int16)temp;

}

Int16 halfband(Int16 input, Int16* z_x, Int16* z_y, Int16 lowpass)
{
     return 0;
}


float second_order_IIR_Direct_Form_II_f(float input, float* coefficients, float* history) {
	float accum = 0;
	float temp = 0;

    accum = input;
    accum -= coefficients[4]*history[0];
    accum -= coefficients[5]*history[1];

    temp = accum;

    accum = coefficients[0] * accum;
    accum += coefficients[1] * history[0];
    accum += coefficients[2] * history[1];

    history[1] = history[0];
    history[0] = temp;

    return accum;
}

