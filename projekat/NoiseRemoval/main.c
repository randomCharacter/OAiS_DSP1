//////////////////////////////////////////////////////////////////////////////
// *
// * Predmetni projekat iz predmeta OAiS DSP 1
// * Godina: 2017
// *
// * Zadatak: Uklanjanje periodicnog suma upotrebom notch filtra
// * Autor:   Mario Peric
// *                                                                          
// *                                                                          
//////////////////////////////////////////////////////////////////////////////

#include "stdio.h"
#include "ezdsp5535.h"
#include "ezdsp5535_i2c.h"
#include "aic3204.h"
#include "ezdsp5535_aic3204_dma.h"
#include "ezdsp5535_i2s.h"
#include "print_number.h"
#include "math.h"
#include "Dsplib.h"
#include "window.h"

#include "stdio.h"
#include "ezdsp5535.h"
#include "ezdsp5535_i2c.h"
#include "aic3204.h"
#include "ezdsp5535_aic3204_dma.h"
#include "ezdsp5535_i2s.h"
#include "ezdsp5535_sar.h"
#include "print_number.h"
#include "math.h"
#include "Dsplib.h"
#include "filters.h"
#include "iir.h"

/* Frekvencija odabiranja */
#define SAMPLE_RATE 8000L

/* Velicina prozora za racunanje FFT-a */
/* TODO Dodeliti velicinu bloka kod racunanja FFT*/
#define FFT_SIZE 128

/* Niz za smestanje odbiraka ulaznog signala */
#pragma DATA_ALIGN(InputBufferL,4)
Int16 InputBufferL[AUDIO_IO_SIZE];
#pragma DATA_ALIGN(InputBufferR,4)
Int16 InputBufferR[AUDIO_IO_SIZE];
#pragma DATA_ALIGN(OutputBufferL,4)
Int16 OutputBufferL[AUDIO_IO_SIZE];
#pragma DATA_ALIGN(OutputBufferR,4)
Int16 OutputBufferR[AUDIO_IO_SIZE];
#pragma DATA_ALIGN(buffer,4)
Int16 buffer[FFT_SIZE];
Int32 magnitude_response[FFT_SIZE/2];

Int16 x_history1[AUDIO_IO_SIZE];
Int16 y_history1[AUDIO_IO_SIZE];
Int16 x_history2[AUDIO_IO_SIZE];
Int16 y_history2[AUDIO_IO_SIZE];

int coefs[4] = {19, 26, 38, 46};


Int16 *filters[4] = { IIR_1200Hz_2nd_order, IIR_1650Hz_2nd_order, IIR_2400Hz_2nd_order, IIR_2850Hz_2nd_order };

void main( void )

{
	/* Inicijalizaija razvojne ploce */
	EZDSP5535_init( );

    /* Inicijalizacija LCD kontrolera */
	initPrintNumber();

	printf("\n Uklanjanje sinusoidalnog suma iz signala \n");

    /* Inicijalizacija veze sa AIC3204 kodekom (AD/DA) */
    aic3204_hardware_init();
	
    /* Inicijalizacija AIC3204 kodeka */
	aic3204_init();

    aic3204_dma_init();

    /* Postavljanje vrednosti frekvencije odabiranja i pojacanja na kodeku */
    set_sampling_frequency_and_gain(SAMPLE_RATE, 0);

    int kraj = 1;
    int i, j, k = 0;
    int a_old;

    while(1)
	{
		aic3204_read_block(InputBufferL, InputBufferR);

		/* rfft menja bafer, pa ga je potrebno kopirati */
		for (i = 0; i < AUDIO_IO_SIZE; i++) {
			buffer[i] = InputBufferL[i];
		}

		/* Prozoriranje */
		for(j=0; j < FFT_SIZE; j++) {
			buffer[j] = _smpy(InputBufferL[j], p_window[j]);
		}

		rfft(buffer, FFT_SIZE, SCALE);

		magnitude_response[0] =  (Int32)buffer[0]*buffer[0];
		for (j=1; j < AUDIO_IO_SIZE/2; j++)
		{
			magnitude_response[j] = (Int32)buffer[2*j]*buffer[2*j]+(Int32)buffer[2*j+1]*buffer[2*j+1];

		}

		/* Indeks i vrednost maksimalnog odziva */
		Int32 max_mr = magnitude_response[0];
		int max_i = 0;

		for (i = 0; i < AUDIO_IO_SIZE / 2; i++) {
			if (magnitude_response[i] > max_mr) {
				max_mr = magnitude_response[i];
				max_i = i;
			}
		}

		int a = -1;
		for (i = 0; i < 4; i++) {
			if (max_i == coefs[i]) {
				a = i;
				break;
			}
		}
		/* Ako nadje novu frekvenciju prazni istoriju */
		if (a != a_old) {
			for (i = 0; i < AUDIO_IO_SIZE; i++) {
				x_history1[i] = 0;
				y_history1[i] = 0;
				x_history2[i] = 0;
				y_history2[i] = 0;
			}
		}

		if (a != -1) {
			a_old = a;
		}

		/* Primenjuje IIR */
		for (i = 0; i < AUDIO_IO_SIZE; i++) {
			OutputBufferL[i] = second_order_IIR(InputBufferL[i], filters[a_old], x_history1, y_history1);
			OutputBufferR[i] = second_order_IIR(InputBufferR[i], filters[a_old], x_history2, y_history2);
		}

		aic3204_write_block(OutputBufferL, OutputBufferR);
		
		/* Ispisuje redni broj frekvencije koju je nasao */
		// Zakomenarisati zbog ometanja izvršavanja
		clearLCD();
		if (a_old == -1) {
			printChar('8');
		} else {
			printChar('1' + a_old);
		}
	}

    	
	/* Prekid veze sa AIC3204 kodekom */
    aic3204_disable();

    printf( "\n***Kraj programa***\n" );
	SW_BREAKPOINT;
}
