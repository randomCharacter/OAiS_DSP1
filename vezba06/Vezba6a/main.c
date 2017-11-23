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
#include "stdlib.h"
#include "ezdsp5535.h"
#include "ezdsp5535_i2c.h"
#include "aic3204.h"
#include "ezdsp5535_aic3204_dma.h"
#include "ezdsp5535_i2s.h"
#include "delay.h"
#include "echo.h"

#define SAMPLE_RATE 16000L
#define GAIN 30

#pragma DATA_ALIGN(InputBufferL,4)
Int16 InputBufferL[AUDIO_IO_SIZE];
#pragma DATA_ALIGN(InputBufferR,4)
Int16 InputBufferR[AUDIO_IO_SIZE];

#pragma DATA_ALIGN(OutputBufferL,4)
Int16 OutputBufferL[AUDIO_IO_SIZE];
#pragma DATA_ALIGN(OutputBufferR,4)
Int16 OutputBufferR[AUDIO_IO_SIZE];

/*
 *
 *  main( )
 *
 */
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

    /* Call delay init */
    delay_init(8000);

	for(i=0;i<SAMPLE_RATE*100L/AUDIO_IO_SIZE;i++)
	{
		aic3204_read_block(InputBufferL, InputBufferR);

		for(j=0; j < AUDIO_IO_SIZE; j++)
		{
			/* Your code here */
			OutputBufferR[j] = InputBufferR[j];
			OutputBufferL[j] = delay(InputBufferL[j]);
		}

		aic3204_write_block(OutputBufferL, OutputBufferR);
	}
    	
	/* Disable I2S and put codec into reset */ 
    aic3204_disable();

    printf( "\n***Program has Terminated***\n" );
	SW_BREAKPOINT;
}

