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
#include "ezdsp5535_sdcard.h"

#define BUFFER_SIZE AUDIO_IO_SIZE
#define SAMPLE_RATE 16000L
#define SD_CARD_START_ADDRESS 0xFA000

// Length of recording 10s
static const Int32 n = SAMPLE_RATE/BUFFER_SIZE*10;

#pragma DATA_ALIGN(InputBufferL,4)
Int16 InputBufferL[BUFFER_SIZE];
#pragma DATA_ALIGN(InputBufferR,4)
Int16 InputBufferR[BUFFER_SIZE];

#pragma DATA_ALIGN(OutputBuffer,4)
Int16 OutputBuffer[BUFFER_SIZE];

/*
 *
 *  main( )
 *
 */
void main( void )
{   
	Int32 i = 0;
	Uint32 address = SD_CARD_START_ADDRESS;
    /* Initialize BSL */
    EZDSP5535_init( );

	printf("\n Template DMA loopback\n");
		
    /* Initialise hardware interface and I2C for code */
    aic3204_hardware_init();
	
    /* Initialise the AIC3204 codec */
	aic3204_init();
          
    aic3204_dma_init();
    
	/* Setup sampling frequency and 30dB gain for microphone */
    set_sampling_frequency_and_gain(SAMPLE_RATE, 30);

    EZDSP5535_SDCARD_init();

	for(i = 0; i < BUFFER_SIZE; i++)
	{
		OutputBuffer[i] = 0;
	}
	
	aic3204_write_block(OutputBuffer, OutputBuffer);
	aic3204_write_block(OutputBuffer, OutputBuffer);
	
	for(i = 0; i < n; i++)
	{
		aic3204_read_block(InputBufferL, InputBufferR);
		EZDSP5535_SDCARD_write(address, BUFFER_SIZE*2, (Uint16*)InputBufferL);
		address+=BUFFER_SIZE*2;
	}

	printf("Playing recoreded audio using same sample rate as input (16kHz)");
    address = SD_CARD_START_ADDRESS;
    for(i = 0; i < n; i++)
    {
		EZDSP5535_SDCARD_read(address, BUFFER_SIZE*2, (Uint16*)OutputBuffer);
		address+=BUFFER_SIZE*2;
		aic3204_write_block(OutputBuffer, OutputBuffer);
	}
	
	
	/*  Yout code here */

	/* Close SD card */
	EZDSP5535_SDCARD_close();

	/* Disable I2S and put codec into reset */ 
    aic3204_disable();

    printf( "\n***Program has Terminated***\n" );
	SW_BREAKPOINT;
}

