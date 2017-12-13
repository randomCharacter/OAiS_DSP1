/*****************************************************************************/
/*                                                                           */
/* FILENAME                                                                  */
/* 	 IIR_all_pass_filters.h                                                 */
/*                                                                           */
/* DESCRIPTION                                                               */
/*   Header file for IIR all pass filters.                                  */
/*                                                                           */
/*   The order of the coefficients is B0, B1/2, B2, A0, A1/2, A2, where      */
/*   B0, B1/2 and B2 are the numerator coefficients, A0, A1/2 and A2 are     */
/*   the denominator coefficients.                                           */
/*                                                                           */
/* REVISION                                                                  */
/*   Revision: 1.00	                                                         */
/*   Author  : Dejan Bokan                                                   */
/*****************************************************************************/
#ifndef IIR_ALL_PASS_H
#define IIR_ALL_PASS_H

Int16 IIR_all_pass_2nd_order[6] = {10923, 0, 32767,
								   32767, 0, 10923};
#endif

/*****************************************************************************/
/* End of IIR_all_pass_filters.h                                            */
/*****************************************************************************/
