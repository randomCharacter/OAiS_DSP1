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

#include "stdio.h"
#include "ezdsp5535.h"
#include "ezdsp5535_i2c.h"
#include "aic3204.h"
#include "ezdsp5535_aic3204_dma.h"
#include "ezdsp5535_i2s.h"
#include "math.h"
#include "sine.h"

#define PI 3.141592653589793238

#define SAMPLE_RATE 48000L
#define GAIN 0

#pragma DATA_ALIGN(InputBufferL,4)
Int16 InputBufferL[AUDIO_IO_SIZE];
#pragma DATA_ALIGN(InputBufferR,4)
Int16 InputBufferR[AUDIO_IO_SIZE];

Int16 zeros[AUDIO_IO_SIZE];

Int32 DFTReal[AUDIO_IO_SIZE];
Int32 DFTImag[AUDIO_IO_SIZE];

Int32 magnitude[AUDIO_IO_SIZE/2];
/*
 *
 *  main( )
 *
 */

void dft(float inreal[], float inimag[], float outreal[], float outimag[], Int16 N)
{
	int n, k;
    for ( n = 0; n < N; n++) {
        float sumreal = 0;
        float sumimag = 0;
        for (k = 0; k < N; k++) {
            sumreal +=  inreal[k] * cos(2 * PI * n * k / N) + inimag[k] * sin(2 * PI * n * k / N);
            sumimag += -inreal[k] *  sin(2 * PI * n * k / N) + inimag[k] * cos(2 * PI * n * k / N);
        }
        outreal[n] = sumreal;
        outimag[n] = sumimag;
    }
}

// TO DO: finish DFT function
void dft_int(Int16 inreal[], Int16 inimag[], Int32 outreal[], Int32 outimag[], Uint16 N)
{
	Uint16 n, k;

	// calculate scale_factor
	int scale_factor = 65536 / N;

	for ( n = 0; n < N; n++)
	{
		Int32 sumreal = 0;
	    Int32 sumimag = 0;

	    for (k = 0; k < N; k++)
	    {
	    	// calculate DFT inner loop
	    	sumreal += (Int32) _smpy(inreal[k], cos_LT(n * k * scale_factor)) + _smpy(inimag[k], sin_LT(n * k * scale_factor));
	    	sumimag += (Int32) _smpy(-inreal[k], sin_LT(n * k * scale_factor)) + _smpy(inimag[k], cos_LT(n * k * scale_factor));

	    }

	    // store calculated values into output buffers
	    outreal[n] = sumreal;
	    outimag[n] = sumimag;
	}
}

void main( void )
{   
	int i, j;

	/* Initialize BSL */
    EZDSP5535_init( );

	printf("\n Template DMA loopback\n");
		
    /* Initialise hardware interface and I2C for code */
    aic3204_hardware_init();
	
    /* Initialise the AIC3204 codec */
	aic3204_init();
          
    aic3204_dma_init();
    
    /* Setup sampling frequency and 30dB gain for microphone */
    set_sampling_frequency_and_gain(SAMPLE_RATE, GAIN);

    for(i = 0; i < AUDIO_IO_SIZE; i++)
    {
    	zeros[i] = 0;
    }

	for(i=0;i<SAMPLE_RATE*100L/AUDIO_IO_SIZE;i++)
	{
		aic3204_read_block(InputBufferL, InputBufferR);

		dft_int(InputBufferL, zeros, DFTReal, DFTImag, AUDIO_IO_SIZE);

		for (j=0; j < AUDIO_IO_SIZE / 2; j++)
				{
					magnitude[j] = (Int32)DFTReal[j]*DFTReal[j]+(Int32)DFTImag[j]*DFTImag[j];

				}

	}
    	
	/* Disable I2S and put codec into reset */ 
    aic3204_disable();

    printf( "\n***Program has Terminated***\n" );
	SW_BREAKPOINT;
}

