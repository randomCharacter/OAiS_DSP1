#include "gen_sinus.h"
#include "math.h"

#define PI 3.14159265

void gen_sinus_multiton(int n, double a, double f0, double df, double ph, double buffer[])
{
	int i = 0;
	double f = f0;
    for(i = 0; i < n; i++)
    {
    		buffer[i] = a*sin(2*PI*f*i+ph);
    }
    f+=df;
   	while(f< 0.5)
   	{
   		for(i = 0; i < n; i++)
    	{
    		buffer[i] += a*sin(2*PI*f*i+ph);
    	}
    	f+=df;
    }
}


void gen_log_sweep(int n, double a, double f1, double f2, double ph0, double buffer[])
{
    int i = 0;
    double ph_t = 0;
    for(i = 0; i < n; i++)
    {
    	ph_t = (n*f1/log(f2/f1))*exp((i*log(f2/f1))/n)*2*PI+ph0;
    	buffer[i] = a*sin(ph_t);
    }
}
