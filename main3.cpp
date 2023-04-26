#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include "kwad.h"
#include "nonlin.h"

double funkcjapoczatkowa(double x) //losowa funkcja z dupy
{
	return sin(cos(x*x));
}

int main()
{
	int N = 0;
	double wartosc = 0;
	while ((int)N > 50 || (int)N < 2)   //zeby na pewno dobrze wpisali
	{
		printf("Podaj liczbe calkowita N, z przedzialu (1,50>: \n");
		scanf("%d", &N);
		system("CLS"); //czyszczenie ekranu
		printf("Niepoprawne dane\n");
	} 
	double *tabx = (double*)malloc(N * sizeof(double));	//tablice na wartosci zinterpolowane
	double *taby = (double*)malloc(N * sizeof(double));
	for (int i = 1; i <= N; i++)
	{
		wartosc = trapez(0, i, funkcjapoczatkowa, 200);
		printf("Wartosc calki z funkcji od 0 do %d: %d\n", i, wartosc);
		tabx[i - 1] = i;
		taby[i - 1] = wartosc;
	}

	return 0;
}
