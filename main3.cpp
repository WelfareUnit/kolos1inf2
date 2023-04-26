#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include "kwad.h"
#include "nonlin.h"
double k = 1;

double funkcjawew(double x) //funkcja podca³kowa
{
	return cos(k * 3.14159265359* x );
}

double funkcjaodalfa(double alfa) //funkcja liczaca calke
{
	return trapez(0, alfa, funkcjawew, 2000); //2000 z dupy wziete zeby bylo dokladnie
}

int main()
{
	int alfa = 1;
	int N = 0;
	int epsilon = 0.0001;
	do   //¿eby na pewno dobrze wpisali
	{
		printf("Podaj liczbe calkowita N, z przedzialu (1,200>: \n");
		scanf("%d", &N);
		system("CLS"); //czyszczenie ekranu
		printf("Niepoprawne dane\n");
		N = -1;
	} while ((int)N > 200 || (int)N < 2);
	int iter = 0;
	double miejsce_zerowe = 0;
	for (int i = 1; i <= N; i++)
	{
		k = i;
		miejsce_zerowe = bisec(0, k, funkcjaodalfa,epsilon,&iter);
		printf("Dla k = %d, miejsce zerowe to: %lf, liczba iteracji: %d\n", i, miejsce_zerowe, iter);
	}

	return 0;
}
