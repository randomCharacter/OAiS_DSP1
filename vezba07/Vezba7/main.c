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
#include "fir.h"
#include "low_pass_32th_order.h"
#include "high_pass_32th_order.h"
#include "band_pass_32th_order.h"



#define SAMPLE_RATE 48000L
#define GAIN 0

#pragma DATA_ALIGN(InputBufferL,4)
Int16 InputBufferL[AUDIO_IO_SIZE];
#pragma DATA_ALIGN(InputBufferR,4)
Int16 InputBufferR[AUDIO_IO_SIZE];

#pragma DATA_ALIGN(OutputBufferL,4)
Int16 OutputBufferL[AUDIO_IO_SIZE];
#pragma DATA_ALIGN(OutputBufferR,4)
Int16 OutputBufferR[AUDIO_IO_SIZE];

/* Define history buffers and Rd/Wr pointers*/
Uint16 state1;
Uint16 state2;
Uint16 state3;
Int16 buffer1[AUDIO_IO_SIZE];
Int16 buffer2[AUDIO_IO_SIZE];
Int16 buffer3[AUDIO_IO_SIZE];

Int16 history1[AUDIO_IO_SIZE];
Int16 history2[AUDIO_IO_SIZE];
Int16 history3[AUDIO_IO_SIZE];

/*
 *
 *  main( )
 *
 */
void main( void )
{   
	int i;

	/* Initialize BSL */
    EZDSP5535_init( );

	printf("\n Vezba 7 \n");
		
    /* Initialise hardware interface and I2C for code */
    aic3204_hardware_init();
	
    /* Initialise the AIC3204 codec */
	aic3204_init();
          
    aic3204_dma_init();
    
    /* Setup sampling frequency and 30dB gain for microphone */
    set_sampling_frequency_and_gain(SAMPLE_RATE, 0);

    /* Initialize history buffers to 0 */
    for (i = 0; i < AUDIO_IO_SIZE; i++) {
    	history1[i] = 0;
    	history2[i] = 0;
    	history3[i] = 0;
    }


	for(i=0;i<SAMPLE_RATE*100L/AUDIO_IO_SIZE;i++)
	{
		aic3204_read_block(InputBufferL, InputBufferR);

		for(i = 0; i < AUDIO_IO_SIZE; i++)
		{
			buffer1[i] = fir_circular(InputBufferL[i], lowpass_5kHz_32th_order,
					history1, LP_LENGTH, &state1);
			buffer2[i] = fir_circular(InputBufferL[i], highpass_12kHz_32th_order,
					history2, HP_LENGTH, &state2);
			buffer3[i] = fir_circular(InputBufferL[i], bandpass_5kHz_12kHz_32th_order,
					history3, BP_LENGTH, &state3);
			OutputBufferR[i] = InputBufferR[i];
			OutputBufferL[i] = _smpy(0.75 * 32768, buffer1[i]) + buffer3[i] + _smpy(0.5 * 32768, buffer2[i]);
		}
		aic3204_write_block(OutputBufferL, OutputBufferR);
	}
    	
	/* Disable I2S and put codec into reset */ 
    aic3204_disable();

    printf( "\n***Program has Terminated***\n" );
	SW_BREAKPOINT;
}

