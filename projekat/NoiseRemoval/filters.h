/*****************************************************************************/
/*                                                                           */
/* FILENAME                                                                  */
/* 	 filters.h                                                  */
/*                                                                           */
/* DESCRIPTION                                                               */
/*   Header file for IIR low pass filters.                                   */
/*   The order of the coefficients is B0, B1/2, B2, A0, A1/2, A2, where      */
/*   B0, B1/2 and B2 are the numerator coefficients, A0, A1/2 and A2 are     */
/*   the denominator coefficients.                                           */
/*                                                                           */
/* REVISION                                                                  */
/*   Revision: 1.00	                                                         */
/*   Author  : Mario Peric                                                   */
/*****************************************************************************/

#ifndef FILTERS_H_
#define FILTERS_H_

#define r 0.9

// Filteri izgerisani za datu frekvenciju sa r = 1
// B0, B1/2, B2, A0, A1/2, A2
Int16 IIR_1200Hz_2nd_order[6] = { 32767, -19273, 32767, 32767, -19273*r, 32767*r*r };
Int16 IIR_1650Hz_2nd_order[6] = { 32767,  -8915,  32767, 32767, -8915*r, 32767*r*r };
Int16 IIR_2400Hz_2nd_order[6] = { 32767, 10096, 32767, 32767, 10096*r, 32767*r*r };
Int16 IIR_2850Hz_2nd_order[6] = { 32767, 20257, 32767, 32767, 20257*r, 32767*r*r };

#endif /* FILTERS_H_ */
