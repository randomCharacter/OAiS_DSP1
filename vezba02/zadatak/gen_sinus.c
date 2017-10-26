#include "tistdtypes.h"
#include "gen_sinus.h"
#include "sine_table.h"
#include "math.h"

#define PI 3.14159265

void gen_sinus(int n, float a, float f, float ph, float buffer[])
{
	int i;
	for (i=0; i<n; i++)
	{
		buffer[i] = a * sin(2 * PI * f * i + ph);
	}
}

void gen_sinus_table(int n, float a, float f, float ph, float buffer[])
{
    int i = 0;
    int delta = f * SINE_TABLE_SIZE;
    int k = (ph/(2*PI)*SINE_TABLE_SIZE);
    int mask = (SINE_TABLE_SIZE-1);

    for (i = 0; i < n; i++)
    {
        k = k & mask;
        if (k < SINE_TABLE_SIZE / 4)
        {
            buffer[i] = a*p_sine_table[k];
            k+=delta;
        }
        else if (k < SINE_TABLE_SIZE / 2)
        {
        	buffer[i] = a*p_sine_table[SINE_TABLE_SIZE / 2 - k];
            k+=delta;
        }
        else if (k < 3 * SINE_TABLE_SIZE / 4)
        {
        	buffer[i] = -a*p_sine_table[k - SINE_TABLE_SIZE / 2];
            k+=delta;
        }
        else
        {
        	buffer[i] = -a*p_sine_table[SINE_TABLE_SIZE - k];
            k+=delta;
        }
    }
}


void gen_sinus_multiton(int n, float a, float f0, float df, float ph, float buffer[])
{
	int i = 0;
	float f = 0.0;

	for (i = 0; i < n; i++)
	{
		buffer[i] = 0;
	}

	for (f = f0; f < 0.5; f += df)
	{
		for (i = 0; i < n; i++) {
			buffer[i] += sin(2 * PI * f * i + ph);
		}
	}

	for (i = 0; i < n; i++)
	{
		buffer[i] *= a / f;
	}
}

void gen_lin_sweep(int n, float a, float f1, float f2, float ph, float buffer[])
{
    int i = 0;
    float ph_t = 0;
    for(i = 0; i < n; i++)
    {
    	ph_t = 2*PI*(f1*i + (f2-f1)/(2*n)*i*i) + ph;
    	buffer[i] = a*sin(ph_t);
    }
}

void gen_log_sweep(int n, float a, float f1, float f2, float ph, float buffer[])
{
    int i = 0;
    float ph_t = 0;
    for(i = 0; i < n; i++)
    {
    	ph_t = (n*f1/log(f2/f1))*exp((i*log(f2/f1))/n)*2*PI+ph;
    	buffer[i] = a*sin(ph_t);
    }
}

void gen_square(int n, float a, float f, float D, float buffer[])
{
	int i = 0, j=0;
 	int T = 1/f;
 	int Tmax = D*T/100;

	for(i = 0; i < n; i++)
	{
		if(j < Tmax)
		{
			buffer[i] = a;
		}
		else if(j < T)
		{
			buffer[i] = 0;
		}
		else
		{
			j = 0;
			buffer[i] = a;
		}
		j++;
	}
}
