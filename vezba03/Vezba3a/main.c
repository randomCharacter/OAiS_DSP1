//////////////////////////////////////////////////////////////////////////////
// * File name: main.c
// *
// * Description:  Main function.
// *
// * Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/
// * Copyright (C) 2011 Spectrum Digital, Incorporated
// *
// *
// *
//////////////////////////////////////////////////////////////////////////////

#include <cstdio>
#include "ezdsp5535.h"
#include "gen_sinus.h"

#define N 2000

double sin_multitone_48kHz[N];
double sin_multitone_24kHz[N];

double freq_sweep_48kHz[N];
double freq_sweep_24kHz[N];
double freq_sweep_16kHz[N];

/*
 *
 *  main( )
 *
 */
void main( void )
{
	unsigned long int i = 0;

	/* Signal gen parameters */
    double sample_frequency = 48000.0;
    double amplitude = 10.0;
    double phase = 0.0;

    /* Multitione parameters*/
    double f0 = 1000.0;
    double dF = 5000.0;

    /* Log sweep parameters */
    double f1 = 1000.0;
    double f2 = 10000.0;

	printf("\n Vezba3 - Zadatak 1 \n");

	gen_sinus_multiton(N, amplitude, f0/sample_frequency, dF/sample_frequency, phase, sin_multitone_48kHz);
	
	for(i = 0; i < N/2; i++)
	{
		sin_multitone_24kHz[i] = sin_multitone_48kHz[2*i];
	}

	gen_log_sweep(N, amplitude, f1/sample_frequency, f2/sample_frequency, phase, freq_sweep_48kHz);

	for(i = 0; i < N/2; i++)
	{
		freq_sweep_24kHz[i] = freq_sweep_48kHz[2*i];
	}

	for(i = 0; i < N/3; i++)
	{
		freq_sweep_16kHz[i] = freq_sweep_48kHz[2*i];
	}

	printf( "\n***Program has Terminated***\n" );
	SW_BREAKPOINT;
}

