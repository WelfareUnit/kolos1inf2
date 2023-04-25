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
    //mamy dane, wprowadŸmy je - talbice bêd¹ 5cioelementowe statyczne na pocz¹tku, bo tak¹ mamy tabelkê
    double x[5] = { -1.0,0.0,1.0,2.0,3.0}; //double, ¿eby siê dobrze mno¿y³o
    double y[5] = { -2.5,-1.5,-1,0.25,0.75 }; //liczby z kropk¹

    //1. Przeprowadziæ interpolacjê danych z krokiem h - 0.025
    double h = 0.025;
    //tu mo¿na na kilka sposobów, zobaczymy
    //sprawdzamy, ile bêdzie potrzebne kroków
    int ilekroków =(int)(x[4] - x[0])/h; //ofc elementy tablicy liczy siê od 0; dzielimy szerokoœæ dziedziny na krok i mamy ile kroków musimy przejœc
    double* interpolowanex = (double *)malloc(ilekroków*sizeof(double));
    double* interpolowanex = (double *)malloc(ilekroków*sizeof(double));
    int pom = 0;
    for (double i = x[0]; i <= x[4]; i += h) //zaczynamy od pierwszego elementu z tablicy i lecimy do ostatniego co krok interpolowania
    {
        x[pom] = i;
        y[pom] = lagrange(x, y, 5, i); //interpoluje wartoœæ y(i) na podstawie wartoœci wprowadzeonej na pocz¹tku
    }
    //2. zapisaæ do pliku, dwie kolumny
    FILE* f;
    f = fopen("interpol.txt", "w");
    fprintf(f, "x\ty\n"); //nag³ówek pliku
    for (int i = 0; i < ilekroków;i++)
    {
        fprintf(f,"%d\t%d\n", x[i], y[i]); //drukowanie do pliku po tabulatorku
    }

    return 0;
}
