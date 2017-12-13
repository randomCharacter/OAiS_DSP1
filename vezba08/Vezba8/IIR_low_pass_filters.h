/*****************************************************************************/
/*                                                                           */
/* FILENAME                                                                  */
/* 	 IIR_low_pass_filters.h                                                  */
/*                                                                           */
/* DESCRIPTION                                                               */
/*   Header file for IIR low pass filters.                                   */
/*   The order of the coefficients is B0, B1/2, B2, A0, A1/2, A2, where      */
/*   B0, B1/2 and B2 are the numerator coefficients, A0, A1/2 and A2 are     */
/*   the denominator coefficients.                                           */
/*                                                                           */
/* REVISION                                                                  */
/*   Revision: 1.00	                                                         */
/*   Author  : Dejan Bokan                                                   */
/*****************************************************************************/

#ifndef IIR_LOW_PASS_FILTERS_H
#define IIR_LOW_PASS_FILTERS_H

Int16 IIR_low_pass_5000Hz_2nd_order[6] = { 2360,  2360,  2360,
													 32767, -18118, 12907};


Int16 IIR_low_pass_5000Hz_4th_order[2][6] = { { 6282,  -4240,  6281,
														   32767, -26001, 28298},
														 { 4415,  -131,   4379,
														   32767, -23752, 18722}};

Int16 IIR_low_pass_5000Hz_6th_order[3][6] = { { 1135,  635,    1004,
														   32767, -23337, 17315 },
		                                                 { 15188, -10526, 15185,
		                                                   32767, -26383, 29713 },
														 { 7405,  -3857,  7319,
														   32767, -24596, 23177 } };
#endif

/*****************************************************************************/
/* End of IIR_low_pass_filters.h                                             */
/*****************************************************************************/
