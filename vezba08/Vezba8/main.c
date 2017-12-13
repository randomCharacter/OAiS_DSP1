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
#include "iir.h"
#include "IIR_low_pass_filters.h"


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

Int16 x_history1[AUDIO_IO_SIZE];
Int16 y_history1[AUDIO_IO_SIZE];
Int16 x_history2[AUDIO_IO_SIZE][2];
Int16 y_history2[AUDIO_IO_SIZE][2];
Int16 delta[AUDIO_IO_SIZE];

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

	printf("\n Vezba 8 \n");
		
    /* Initialise hardware interface and I2C for code */
    aic3204_hardware_init();
	
    /* Initialise the AIC3204 codec */
	aic3204_init();
          
    aic3204_dma_init();
    
    /* Setup sampling frequency and 30dB gain for microphone */
    set_sampling_frequency_and_gain(SAMPLE_RATE, GAIN);

    /* Initialize history buffers to 0 */
    for (i = 0; i < AUDIO_IO_SIZE; i++) {
    	x_history1[i] = 0;
    	y_history1[i] = 0;
    	for (j = 0; j < 2; j++) {
			x_history2[i][j] = 0;
			y_history2[i][j] = 0;
    	}
    	if (i == 0) {
    		delta[i] = 16000;
    	} else {
    		delta[i] = 0;
    	}
    }


	for(i=0;i<SAMPLE_RATE*100L/AUDIO_IO_SIZE;i++)
	{
		aic3204_read_block(InputBufferL, InputBufferR);
		for (j = 0; j < AUDIO_IO_SIZE; j++)
		{
			OutputBufferL[j] = InputBufferL[j];
			OutputBufferR[j] = InputBufferR[j];
		}

		for(i = 0; i < AUDIO_IO_SIZE; i++)
		{
			//OutputBufferL[i] = second_order_IIR(InputBufferL[i], IIR_low_pass_5000Hz_2nd_order, x_history1, y_history1);
			//OutputBufferR[i] = fourth_order_IIR(InputBufferR[i], IIR_low_pass_5000Hz_4th_order, x_history2, y_history2);
			//OutputBufferL[i] = Nth_order_IIR(InputBufferL[i], IIR_low_pass_5000Hz_2nd_order, x_history1, y_history1, 2);
			//OutputBufferR[i] = second_order_IIR(InputBufferR[i], IIR_all_pass_2nd_order, x_history1, y_history1);
			OutputBufferL[i] = halfband(delta[i], x_history1, y_history1, 1);
			OutputBufferR[i] = Nth_order_IIR(InputBufferR[i], IIR_low_pass_5000Hz_4th_order, x_history2, y_history2, 4);
		}

		aic3204_write_block(OutputBufferL, OutputBufferR);
	}
    	
	/* Disable I2S and put codec into reset */ 
    aic3204_disable();

    printf( "\n***Program has Terminated***\n" );
	SW_BREAKPOINT;
}
