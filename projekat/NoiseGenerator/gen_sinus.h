//////////////////////////////////////////////////////////////////////////////
// *
// * Predmetni projekat iz predmeta OAiS DSP 1
// * Godina: 2017
// *
// * Generisanje Sinusnog signala upotrebom tabele pretrazivanja
// *
//////////////////////////////////////////////////////////////////////////////

#ifndef DTMF_PREDAJNIK_GEN_SINUS_H_
#define DTMF_PREDAJNIK_GEN_SINUS_H_


/********************************************************************
 * Generisanje sinusnog signala upotrebom tabele pretrazivanja
 *   n - broj odbiraka
 *   a - amplituda (u opsegu 0 - 1.0)
 *   f - frekvencija (normalizovana)
 *   ph - fazni pomeraj
 *   buffer - niz u kome ce biti smesten izlazni signal
 *********************************************************************/
extern Int32 gen_sinus_table(Int16 n, Int16 a, float f, Int32 k, Int16 buffer[]);

#endif /* DTMF_PREDAJNIK_GEN_SINUS_H_ */
