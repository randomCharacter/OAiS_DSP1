/*
 * Discrete-Time FIR Filter (real)
 * -------------------------------
 * Filter Structure  : Direct-Form FIR
 * Filter Length     : 33
 * Stable            : Yes
 * Linear Phase      : Yes (Type 1)
 * Arithmetic        : fixed
 * Numerator         : s16,15 -> [-1 1)
 * Input             : s16,15 -> [-1 1)
* Type				 : BAND PASS
* Fs				 : 48 kHz
* Fc				 : 12 kHz
*/

#include "tistdtypes.h"

#define BP_LENGTH 33
Int16 bandpass_5kHz_12kHz_32th_order[33] = {
      118,   -116,    -64,     66,   -408,   -917,   -164,   1082,    835,
      -10,   1049,   2125,  -1228,  -6516,  -5026,   4130,   9718,   4130,
    -5026,  -6516,  -1228,   2125,   1049,    -10,    835,   1082,   -164,
     -917,   -408,     66,    -64,   -116,    118
};
