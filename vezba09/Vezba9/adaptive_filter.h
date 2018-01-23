
#ifndef ADAPTIVE_FILTER_H_
#define ADAPTIVE_FILTER_H_

#include "tistdtypes.h"

#define FILTER_ORDER 20

Int16 lms_filter(Int16 signal, Int16 noise, Int16 *coeffs, Int16 *history, Uint16 n_coeff, Uint16 *p_state, Int16 mi);
//Int16 nlms_filter(Int16 signal, Int16 noise, Int16 *coeffs, Int16 *history, Uint16 n_coeff, Uint16 *p_state, Int16 mi);

#endif /* ADAPTIVE_FILTER_H_ */
