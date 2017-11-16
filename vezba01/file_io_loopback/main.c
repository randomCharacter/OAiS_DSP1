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

#define BUFFER_LENGTH 256
#define FILE_SIZE 65536

Uint16 input_buffer[BUFFER_LENGTH];
Uint16 output_buffer[BUFFER_LENGTH];

/*
 *
 *  main( )
 *
 */
void main( void )
{
	unsigned long int i = 0;
	unsigned long int j = 0;

	FILE* input_file = fopen("input.dat", "rb");
	FILE* output_file = fopen("output.dat", "wb");

	printf("\n File I/O loopback \n");

	
	for(j = 0; j < FILE_SIZE/BUFFER_LENGTH; j++)
	{
		fread(input_buffer, sizeof(Int16), BUFFER_LENGTH, input_file);

		for(i = 0; i < BUFFER_LENGTH; i++)
		{
			output_buffer[i] = input_buffer[i];
		}

		fwrite(output_buffer, sizeof(Int16), BUFFER_LENGTH, output_file);
	}

	printf( "\n***Program has Terminated***\n" );
	SW_BREAKPOINT;
}

