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
#include "adaptive_filter.h"
#include "low_pass_8th_order.h"
#include "fir.h"
#include "stdint.h"
#include "IIR_low_pass_filters.h"

#define SAMPLE_RATE 8000L
#define GAIN 0

#pragma DATA_ALIGN(InputBufferL,4)
Int16 InputBufferL[AUDIO_IO_SIZE];
#pragma DATA_ALIGN(InputBufferR,4)
Int16 InputBufferR[AUDIO_IO_SIZE];

#pragma DATA_ALIGN(OutputBufferL,4)
Int16 OutputBufferL[AUDIO_IO_SIZE];
#pragma DATA_ALIGN(OutputBufferR,4)
Int16 OutputBufferR[AUDIO_IO_SIZE];

Int16 adaptive_coeff[FILTER_ORDER] = {0};
Int16 history[FILTER_ORDER] ={0};
Int16 historyX[FILTER_ORDER][3] ={0};
Int16 historyY[FILTER_ORDER][3] ={0};
Uint16 state = 0;

/*
 *
 *  main( )
 *
 */
void main( void )
{   
	int i, j;
	Uint16 n = 0;
    /* Initialize BSL */
    EZDSP5535_init( );

	printf("\n Vezba 9 \n");
		
    /* Initialise hardware interface and I2C for code */
    aic3204_hardware_init();
	
    /* Initialise the AIC3204 codec */
	aic3204_init();
          
    aic3204_dma_init();
    
    /* Setup sampling frequency and 30dB gain for microphone */
    set_sampling_frequency_and_gain(SAMPLE_RATE, GAIN);

    /* Initialize filter coeff */
    /* Your code here */
	for(i=0; i < FILTER_ORDER; i++)
	{
		history[i] = 0;
		adaptive_coeff[i] = 0;
	}

	for(i = 0; i < SAMPLE_RATE*600L/AUDIO_IO_SIZE; i++)
	{
		aic3204_read_block(InputBufferL, InputBufferR);
		for(j=0; j < AUDIO_IO_SIZE; j++)
		{
			/* Your code here */
			OutputBufferR[j] = fourth_order_IIR(InputBufferL[j], IIR_low_pass_5000Hz_4th_order, historyX, historyY);
			OutputBufferL[j] = lms_filter(InputBufferL[j], OutputBufferR[j], adaptive_coeff, history, FILTER_ORDER, &state, 6553);
			//OutputBufferR[j] = fir_circular(InputBufferL[j], IIR_low_pass_5000Hz_2nd_order, history, n, &state);
		}

		aic3204_write_block(OutputBufferL, OutputBufferR);
	}
    	
	/* Disable I2S and put codec into reset */ 
    aic3204_disable();

    printf( "\n***Program has Terminated***\n" );
	SW_BREAKPOINT;
}

