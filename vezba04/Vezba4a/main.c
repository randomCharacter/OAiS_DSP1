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

#include "signal.h"
#include "vezba4.h"

#define N SIGNAL_LENGTH

Int16 quant_sine[N];
float reconstructed_sine[N];
float quantisation_noise[N];

float sin16_wraparound[N];
float sin16_clip[N];

/*
 *
 *  main( )
 *
 */
void main( void )
{
	unsigned long int i = 0;
	float SNR;
	printf("\n Vezba4 - Zadatak 1 \n");

	/* 4-bit Quantisation */
	for(i = 0; i < N; i++)
	{
		quant_sine[i] = quantB(p_signal[i], 16);
	}
		
	/* 4-bit Reconstruct signal */
	for(i = 0; i < N; i++)
	{
		reconstructed_sine[i] = reconstructB(quant_sine[i], 16);
	}
				
	for(i = 0; i < N; i++)
	{
		quantisation_noise[i] = (reconstructed_sine[i] - p_signal[i]);
	}

	for(i = 0; i < N; i++)
	{
		sin16_clip[i] = reconstructB(clipB(quant_sine[i], 15), 16);
		sin16_wraparound[i] = reconstructB(wrapAroundB(quant_sine[i], 15), 16);
	}

	SNR = snr(p_signal, quantisation_noise, N);
	printf("4-bit quantisation SNR: %f\n", SNR);

	printf( "\n***Program has Terminated***\n" );
	SW_BREAKPOINT;
}

