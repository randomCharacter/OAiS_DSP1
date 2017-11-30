/*
 * Discrete-Time FIR Filter (real)
 * -------------------------------
 * Filter Structure  : Direct-Form FIR
 * Filter Length     : 9
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

#define LP_LENGTH 9

Int16 lowpass_5kHz_8th_order[9] = {
     1106,   2725,   4273,   5386,   5790,   5386,   4273,   2725,   1106
};
