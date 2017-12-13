/*****************************************************************************/
/*                                                                           */
/* FILENAME                                                                  */
/* 	 IIR_band_pass_filters.h                                                 */
/*                                                                           */
/* DESCRIPTION                                                               */
/*   Header file for IIR band pass filters.                                  */
/*                                                                           */
/*   The order of the coefficients is B0, B1/2, B2, A0, A1/2, A2, where      */
/*   B0, B1/2 and B2 are the numerator coefficients, A0, A1/2 and A2 are     */
/*   the denominator coefficients.                                           */
/*                                                                           */
/* REVISION                                                                  */
/*   Revision: 1.00	                                                         */
/*   Author  : Dejan Bokan                                                   */
/*****************************************************************************/
#ifndef IIR_BAND_PASS_H
#define IIR_BAND_PASS_H


Int16 IIR_band_pass_5kHz_12kHz_4th_order[2][6] = { { 2202, 895,    2188,
		 	 	 	 	 	 	 	 	 	 	 	 	 	    32767, -19647, 26377},
															  {	32767, -32767, 32757,
																32767, -5403,  26223} };

Int16 IIR_band_pass_5kHz_12kHz_6th_order[3][6] = { { 6716,  1442,  6716,
																32767, -3824,  28029},
															  { 22721, -20559, 22721,
																32767, -21514, 28005},
															  {	18841, -1568,  20,
																32767, -11774, 21683} };
#endif

/*****************************************************************************/
/* End of IIR_band_pass_filters.h                                            */
/*****************************************************************************/
