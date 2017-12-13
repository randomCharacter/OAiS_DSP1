#ifndef VEZBA8_DIRECT_FORM_IIR_H_
#define VEZBA8_DIRECT_FORM_IIR_H_

Int16 iir_basic(Int16 input, Int16* a_coeffs, Int16* x_history, Uint16 n_a_coeff, Int16* b_coeffs,
				Int16* y_history, Uint16 n_b_coeff);

Int16 iir_circular(Int16 input, Int16* a_coeffs, Int16* x_history, Uint16* x_state, Uint16 n_a_coeff, Int16* b_coeffs,
		Int16* y_history, Uint16* y_state, Uint16 n_b_coeff);

#endif /*VEZBA8_DIRECT_FORM_IIR_H_*/
