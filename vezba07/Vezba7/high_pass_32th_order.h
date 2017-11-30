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
 * Type				 : HIGH PASS
 * Fs				 : 48 kHz
 * Fc				 : 12 kHz
 */

#include "tistdtypes.h"

#define HP_LENGTH 33
Int16 highpass_12kHz_32th_order[33] = {
        0,    185,      0,   -318,      0,    505,      0,   -773,      0,
     1175,      0,  -1856,      0,   3344,      0, -10422,  16449, -10422,
        0,   3344,      0,  -1856,      0,   1175,      0,   -773,      0,
      505,      0,   -318,      0,    185,      0
};
