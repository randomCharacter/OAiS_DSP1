/*****************************************************************************/
/*                                                                           */
/* FILENAME                                                                  */
/* 	 IIR_high_pass_filters.h                                                 */
/*                                                                           */
/* DESCRIPTION                                                               */
/*   Header file for IIR low pass filters.                                   */
/*   The order of the coefficients is B0, B1/2, B2, A0, A1/2, A2, where      */
/*   B0, B1/2 and B2 are the numerator coefficients, A0, A1/2 and A2 are     */
/*   the denominator coefficients.                                           */
/*                                                                           */
/* REVISION                                                                  */
/*   Revision: 1.00	                                                         */
/*   Author  : Dejan Bokan													 */
/*****************************************************************************/

#ifndef IIR_HIGH_PASS_FILTERS_H
#define IIR_HIGH_PASS_FILTERS_H

Int16 IIR_high_pass_12000Hz_4th_order[2][6] = { { 9631,  -1741,  9631,
															 32767, 3253,   26803},
														   { 14842, -10737, 14841,
															 32767, 9128, 8936}};

Int16 IIR_high_pass_12000Hz_6th_order[3][6] = { {   5286, -4528,  5263,
		   	   	   	   	   	   	   	   	   	   	   	   	   	   32767, 9448,  5734},
														   {   23956,-3645, 23956,
															   32767, 2676, 28793},
														   {   15058,-5442, 15057,
															   32767, 5293, 18477}};
#endif

/*****************************************************************************/
/* End of IIR_high_pass_filters.h                                            */
/*****************************************************************************/
