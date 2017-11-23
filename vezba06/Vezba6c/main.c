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

#include "tistdtypes.h"
#include "ezdsp5535.h"
#include "stdio.h"
#include "ezdsp5535_i2c.h"
#include "aic3204.h"

#include "convolution_reverb.h"
#include "signal.h"
#include "impulse_response.h"
#define SIGNAL_LENGTH 100
#define SAMPLE_RATE 8000L
#define GAIN 0

/* For testing purpose, keep output values in buffer, so it could be plotted */
#pragma DATA_SECTION(output_signal, ".output_signal")
Int16 output_signal[SIGNAL_LENGTH];


/*
 *
 *  main( )
 *
 */

void main( void )
{
	Uint16 i = 0;

    /* Initialize BSL */
    EZDSP5535_init( );

    printf("\n Vezba 6 - Zadatak 5 \n");

    /* Initialise hardware interface and I2C for code */
    aic3204_hardware_init();

    /* Initialise the AIC3204 codec */
	aic3204_init();

    /* Setup sampling frequency and 30dB gain for microphone */
    set_sampling_frequency_and_gain(SAMPLE_RATE, GAIN);
    aic3204_codec_write(0, 0);

    /* calculate convolution with room model signal */
   	convolution(signal, SIGNAL_LENGTH, impulse_response, IMPULSE_RESPONSE_LENGTH, output_signal);

    while(1)
    {

    	for(i = 0; i < SIGNAL_LENGTH; i++)
    	{
    		aic3204_codec_write(signal[i], signal[i]);
    	}

    	for(i = 0; i < SIGNAL_LENGTH; i++)
    	{
    	    aic3204_codec_write(output_signal[i], output_signal[i]);
    	}
    }
}

