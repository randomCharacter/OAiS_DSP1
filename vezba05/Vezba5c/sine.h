//////////////////////////////////////////////////////////////////////////////
// *
// * Predmetni projekat iz predmeta OAiS DSP 1
// * Godina: 2015
// *
// * Tabela pretrazivanja koja sluzi za generisanje sinusnih signala
// * Tabela sadrzi vrednosti sinusa u prvom kvadrantu
// * Velicina tabele: 1000 odbiraka
// *
//////////////////////////////////////////////////////////////////////////////

#ifndef _SINE_H_
#define _SINE_H_
#include "tistdtypes.h"

/**************************************************************
 * Funkcija za racunanje sinusa na osnovu tabele pretrazivanja
 *
 * 	x - normalizovana vrednost u opsegu [0, 2*pi)
 * 	povratna vrednost - vredsnost sinusa zadatog ugla u q1.15
 * 						prezentaciji
 *
 *************************************************************/
Int16 sin_LT(Uint16 x);

/**************************************************************
 * Funkcija za racunanje kosinusa na osnovu tabele pretrazivanja
 *
 * 	x - normalizovana vrednost u opsegu [0, 2*pi)
 * 	povratna vrednost - vredsnost kosinusa zadatog ugla u q1.15
 * 						prezentaciji
 *
 *************************************************************/
Int16 cos_LT(Uint16 x);


#endif /* DTMF_PREDAJNIK_SINE_TABLE_H_ */
