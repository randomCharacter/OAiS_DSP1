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
#include "string.h"

Int16 left_input;
Int16 right_input;
Int16 left_output;
Int16 right_output;

#define FS_48kHz 48000L
#define FS_24kHz 24000L
#define FS_16kHz 16000L
#define FS_8kHz 8000L

#define BUFFER_LENGTH 128
#define GAIN_IN_dB 0

typedef struct CircularBuffer_
{
	Int16 *data;
	Int16 read_indx;
	Int16 write_indx;
	size_t size;
} CircularBuffer;

CircularBuffer cbuf;

void circular_buffer_init(CircularBuffer* circular_buffer, Int16* buffer, size_t size)
{
	memset(buffer, 0, size*sizeof(Int16));
	circular_buffer->data = buffer;
	circular_buffer->size = size;
	circular_buffer->read_indx = 0;
	circular_buffer->write_indx = 0;
}

Int16 circular_buffer_read(CircularBuffer* circular_buffer)
{
	Int16 ret;
	if(circular_buffer->read_indx != circular_buffer->write_indx)
	{
		ret = circular_buffer->data[circular_buffer->read_indx];
		circular_buffer->read_indx++;
		circular_buffer->read_indx = circular_buffer->read_indx % (circular_buffer->size-1);
		return ret;
	}
	else
		return 0;
}

void circular_buffer_write(CircularBuffer* circular_buffer, Int16 value)
{
	circular_buffer->data[circular_buffer->write_indx] = value;
	circular_buffer->write_indx++;
	circular_buffer->write_indx = circular_buffer->write_indx % (circular_buffer->size-1);
	if(circular_buffer->read_indx == circular_buffer->write_indx)
	{
		circular_buffer->read_indx++;
		circular_buffer->read_indx = circular_buffer->read_indx % (circular_buffer->size-1);
	}
}

Int16 buffer_left[BUFFER_LENGTH];
Int16 buffer_right[BUFFER_LENGTH];
/*
 *
 *  main( )
 *
 */
void main( void )
{   
	//circular_buffer_init(&cbuf, buffer_left, 1024);
	unsigned long int i = 0;
	unsigned long int j = 0;

    /* Initialize BSL */
    EZDSP5535_init( );

    printf("\n Vezba 3 - Zadatak 2 \n");

    /* Initialise hardware interface and I2C for code */
    aic3204_hardware_init();
	
    /* Initialise the AIC3204 codec */
	aic3204_init();
          
    /* Setup sampling frequency and 30dB gain for microphone */
    set_sampling_frequency_and_gain(FS_24kHz, GAIN_IN_dB);
    

	/* Play Loop for 600 seconds */
    for(i = 0; i < FS_48kHz * 600L; i++)
    {
		aic3204_codec_read(&left_input, &right_input); // Configured for one interrupt per two channels.
               
		left_output = right_input;

	    for(j = 0; j < BUFFER_LENGTH-1; j++)
	    {
	    	buffer_left[j] = buffer_left[j+1];
	    }

	    buffer_left[j] = right_input;

		/*circular_buffer_write(&cbuf, left_input);*/


	    aic3204_codec_write(left_output, left_output);
    }
	
	/* Disable I2S and put codec into reset */ 
    aic3204_disable();

    printf( "\n***Program has Terminated***\n" );
	SW_BREAKPOINT;
}

