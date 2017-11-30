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
 * Type				 : LOW PASS
 * Fs				 : 48 kHz
 * Fc				 : 5 kHz
 */

#include "tistdtypes.h"

#define LP_LENGTH 33

Int16 lowpass_5kHz_32th_order[33] = {
     -522,   -248,    181,    602,    826,    719,    259,   -428,  -1094,
    -1437,  -1199,   -266,   1278,   3154,   4953,   6247,   6718,   6247,
     4953,   3154,   1278,   -266,  -1199,  -1437,  -1094,   -428,    259,
      719,    826,    602,    181,   -248,   -522
};
