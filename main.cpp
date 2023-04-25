#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "gauss.h"
#include "inter.h"
#include "kwad.h"
#include "rk4.h"
#include "winbgi2.h"

int main()
{
    //mamy dane, wprowad�my je - talbice b�d� 5cioelementowe statyczne na pocz�tku, bo tak� mamy tabelk�
    double x[5] = { -1.0,0.0,1.0,2.0,3.0}; //double, �eby si� dobrze mno�y�o
    double y[5] = { -2.5,-1.5,-1,0.25,0.75 }; //liczby z kropk�

    //1. Przeprowadzi� interpolacj� danych z krokiem h - 0.025
    double h = 0.025;
    //tu mo�na na kilka sposob�w, zobaczymy
    //sprawdzamy, ile b�dzie potrzebne krok�w
    int ilekrok�w =(int)(x[4] - x[0])/h; //ofc elementy tablicy liczy si� od 0; dzielimy szeroko�� dziedziny na krok i mamy ile krok�w musimy przej�c
    double* interpolowanex = (double *)malloc(ilekrok�w*sizeof(double));
    double* interpolowanex = (double *)malloc(ilekrok�w*sizeof(double));
    int pom = 0;
    for (double i = x[0]; i <= x[4]; i += h) //zaczynamy od pierwszego elementu z tablicy i lecimy do ostatniego co krok interpolowania
    {
        x[pom] = i;
        y[pom] = lagrange(x, y, 5, i); //interpoluje warto�� y(i) na podstawie warto�ci wprowadzeonej na pocz�tku
    }
    //2. zapisa� do pliku, dwie kolumny
    FILE* f;
    f = fopen("interpol.txt", "w");
    fprintf(f, "x\ty\n"); //nag��wek pliku
    for (int i = 0; i < ilekrok�w;i++)
    {
        fprintf(f,"%d\t%d\n", x[i], y[i]); //drukowanie do pliku po tabulatorku
    }

    return 0;
}
