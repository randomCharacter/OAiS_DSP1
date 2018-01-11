//////////////////////////////////////////////////////////////////////////////
// *
// * Predmetni projekat iz predmeta OAiS DSP 1
// * Godina: 2017
// *
// * Zadatak: Generator periodicnog suma
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
#include "ezdsp5535_sar.h"
#include "print_number.h"
#include "gen_sinus.h"
#include "math.h"

/* Frekvencija odabiranja */
#define SAMPLE_RATE 8000L

/* Niz za smestanje odbiraka ulaznog signala */
#pragma DATA_ALIGN(bufferL,4)
Int16 bufferL[AUDIO_IO_SIZE];
#pragma DATA_ALIGN(bufferR,4)
Int16 bufferR[AUDIO_IO_SIZE];
#pragma DATA_ALIGN(buffer,4)
Int16 buffer[AUDIO_IO_SIZE];


Int32 magnitude_response[AUDIO_IO_SIZE/2];

// Zadate frekvencije
int f[4] = { 1200, 1650, 2400, 2850 };
double f_norm[4] = { (double)f[0] / SAMPLE_RATE, (double)f[1] / SAMPLE_RATE, (double)f[2] / SAMPLE_RATE, (double)f[3] / SAMPLE_RATE };

/* Vraća trenutno pritisnut taster, samo u trenutku pritiskanja */
Uint16 getKey() {
	static Uint16 old = NoKey;
	Uint16 key = EZDSP5535_SAR_getKey();
	if (key == old) {
		return NoKey;
	} else {
		old = key;
		return key;
	}
}


void main( void )
{   
	Int32 count = 0;
	static int f_i = 0;

    /* Inicijalizaija razvojne ploce */
    EZDSP5535_init( );

    /* Inicijalizacija kontrolera za ocitavanje vrednosti pritisnutog dugmeta*/
    EZDSP5535_SAR_init();

    /* Inicijalizacija LCD kontrolera */
    initPrintNumber();

    printf("\n Dodavanje suma u signal \n");
		
    /* Inicijalizacija veze sa AIC3204 kodekom (AD/DA) */
    aic3204_hardware_init();
	
    /* Inicijalizacija AIC3204 kodeka */
	aic3204_init();

    aic3204_dma_init();
    
    /* Postavljanje vrednosti frekvencije odabiranja i pojacanja na kodeku */
    set_sampling_frequency_and_gain(SAMPLE_RATE, 0);

    int i, j;
    Int32 k = 0;

	while(1)
	{
		/* Proverava da li je taster pritisnut */
		// Treba zakomentarisati zbog usporenja
		Uint16 key = getKey();
		if (key == SW1) { // ako je pritisnut SW1
			f_i = (f_i + 1) % 4; //prelazi na sledecu frekvenciju
			clearLCD();
			printChar('1' + f_i);
		}

		aic3204_read_block(bufferL, bufferR);

		/* Generise sinus i u k pamti dokle je stigao */
		k = gen_sinus_table(AUDIO_IO_SIZE, 10000, f_norm[f_i], k, buffer);

		/* Dodavanje suma na ulaz */
		for (i = 0; i < AUDIO_IO_SIZE; i++) {
			/* Klipovanje */
			if ((Int32)bufferL[i] + buffer[i] > 32767) {
				bufferL[i] = 32767;
				bufferR[i] = 32767;

			} else if ((Int32)bufferL[i] + buffer[i] < -32768) {
				bufferL[i] = -32768;
				bufferR[i] = -32768;
			} else {
				bufferL[i] += buffer[i];
				bufferR[i] += buffer[i];
			}
		}

		aic3204_write_block(bufferL, bufferR);

	}
    	
	/* Prekid veze sa AIC3204 kodekom */
    aic3204_disable();

    printf( "\n***Kraj programa***\n" );
	SW_BREAKPOINT;
}


