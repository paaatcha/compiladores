#include "primos.h"

int ser_pri(int p)
{
	int i = 2, flag = 1;
	if (p <= 1)
		return 0;
	if (p == 2)
		return 1;
	else
	{
		while (i < p/2 && flag == 1)
		{
			if (p % i == 0)
				flag = 0;
			i++;
		}
	}
	return flag;
}

int gera_primo_maior_que(int minimo)
{
	int i = minimo;
	while (!ser_pri(i))
	i++;

	return i;
}
