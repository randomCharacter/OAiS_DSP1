#include "tistdtypes.h"
#include "gen_sinus.h"
#include "sine_table.h"
#include "math.h"

#define PI 3.14159265

/********************************************************************
 * Generisanje sinusnog signala upotrebom tabele pretrazivanja
 *   n - broj odbiraka
 *   a - amplituda (u opsegu 0 - 1.0)
 *   f - frekvencija (normalizovana)
 *   ph - fazni pomeraj
 *   buffer - niz u kome ce biti smesten izlazni signal
 *********************************************************************/

Int32 gen_sinus_table(Int16 n, Int16 a, float f, Int32 k, Int16 buffer[])
{
	int i = 0;
	int N = 4 * (SINE_TABLE_SIZE-1);
	int delta = f * N;
	int mask = (N-1);

	for (i = 0; i < n; i++)
	{
		k = k & mask;
		if (k < N / 4)
		{
			buffer[i] = _smpy(a, p_sine_table[k]);
			k+=delta;
		}
		else if (k < N / 2)
		{
			buffer[i] = _smpy(a, p_sine_table[N / 2 - k]);
			k+=delta;
		}
		else if (k < 3 * N / 4)
		{
			buffer[i] = -_smpy(a, p_sine_table[k - N / 2]);
			k+=delta;
		}
		else
		{
			buffer[i] = -_smpy(a, p_sine_table[N - k]);
			k+=delta;
		}
	}
	return k;
}
