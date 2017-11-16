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
#include "aic3204.h"

Int16 left_input;
Int16 right_input;
Int16 left_output;
Int16 right_output;

#define SAMPLES_PER_SECOND 48000
#define BUFFER_LENGTH 1000
#define GAIN_IN_dB 30

unsigned long int i = 0;

/*
 *
 *  main( )
 *
 */
void main( void )
{   
    /* Initialize BSL */
    EZDSP5535_init( );

    printf("\n Audio loopback \n");

    /* Initialise hardware interface and I2C for code */
    aic3204_hardware_init();
	
    /* Initialise the AIC3204 codec */
	aic3204_init();
          
    /* Setup sampling frequency and 30dB gain for microphone */
    set_sampling_frequency_and_gain(SAMPLES_PER_SECOND, GAIN_IN_dB);
    
	/* Play Loop for 600 seconds */
    for ( i = 0 ; i < SAMPLES_PER_SECOND*600L ; i++ )
    {
		aic3204_codec_read(&left_input, &right_input); // Configured for one interrupt per two channels.
               
		left_output = left_input * 2;    
		right_output = right_input / 2;

		aic3204_codec_write(left_output, right_output);
    }
	
	/* Disable I2S and put codec into reset */ 
    aic3204_disable();

    printf( "\n***Program has Terminated***\n" );
	SW_BREAKPOINT;
}

