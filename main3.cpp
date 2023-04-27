#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include "kwad.h"
#include "nonlin.h"
#include "inter.h"
#include "winbgi2.h"
int N = 6;
double* xfunkcji = (double*)malloc(N * sizeof(double));
double* yfunkcji = (double*)malloc(N * sizeof(double));
double funkcjapoczatkowa(double x) //losowa funkcja z dupy
{
	return x+0.6;
}
double zinterpolowane(double x)
{
	return lagrange(xfunkcji, yfunkcji, 6, x);
}

int main()
{
	graphics(800, 600);
	double wartosc = 0;
	double a = -2.0;
	double b = a+N; //tak ¿eby mo¿na by³o zrobiæ N przedzia³ów
	
	double *tabx = (double*)malloc(N * sizeof(double));	//tablice na wartosci calek z przedzialow
	double *taby = (double*)malloc(N * sizeof(double));
	for (int i = 1; i <= N; i++) // calkowanie na kilku przedzialach
	{
		wartosc = trapez(0.0, i, funkcjapoczatkowa, 200);
		printf("Wartosc calki z funkcji od 0 do %d: %lf\n", i, wartosc);
		tabx[i - 1] = i;
		taby[i - 1] = wartosc;
	}
	scale(-3, -3, 3, 3);
	for (int i = 0; i <= b; i++) 
	{
		xfunkcji[i] = i+a;
		yfunkcji[i] = funkcjapoczatkowa(i+a);	//obliczanie kilku elementow z funkjci - analogicznie jak w instrukcji 1
		circle(xfunkcji[i], yfunkcji[i], 5);	
		//rysowanie wezlow interpolacji, kolka zeby odroznic
	}

	int ileiteracji = 0;
	double h = 0.0025; //krok dla funkcji zinterpolowanej
	for (double i = a; i <= b; i+=h) //rysowanie funkcji zinterpolowanej - zaczynamy na poczatku zakresu i idziemy co krok
	{
		point(i, zinterpolowane(i));
		printf("Wartosc interpolowana w punkcie %lf: %lf\n", i, zinterpolowane(i));
	}
	//mozna tez uzyc innych funkcji calkujacych
	printf("Miejscem zerowym wielomianu lagrange funkcji jest :%.4f, iteracji bylo %d",bisec(a, b, zinterpolowane, 0.0001, &ileiteracji),ileiteracji);

	free(tabx);
	free(taby);
	free(xfunkcji);
	free(yfunkcji);
	wait();
	return 0;
}
