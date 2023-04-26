#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "gauss.h"
#include "inter.h"
#include "kwad.h"
#include "rk4.h"
#include "winbgi2.h"
//mamy dane, wprowad�my je - talbice b�d� 5cioelementowe statyczne na pocz�tku, bo tak� mamy tabelk�
int N = 5;
double danex[5] = { -1.0,0.0,1.0,2.0,3.0 }; //double, �eby si� dobrze mno�y�o
double daney[5] = { -2.5,-1.5,-1,0.25,0.75 }; //liczby z kropk�
double funkcjazinterpolowana(double x) //do 3.
{
    return lagrange(danex, daney, 5, x);
}
int main()
{
    //mamy dane, wprowad�my je - talbice b�d� 5cioelementowe statyczne na pocz�tku, bo tak� mamy tabelk�
 

    //1. Przeprowadzi� interpolacj� danych z krokiem h - 0.025
    double h = 0.025;
    //tu mo�na na kilka sposob�w, zobaczymy
    //sprawdzamy, ile b�dzie potrzebne krok�w
    int ilekrok�w =(int)(danex[4] - danex[0])/h; //ofc elementy tablicy liczy si� od 0; dzielimy szeroko�� dziedziny na krok i mamy ile krok�w musimy przej�c
    double* interpolowanex = (double *)malloc(ilekrok�w*sizeof(double));
    double* interpolowaney = (double *)malloc(ilekrok�w*sizeof(double));
    int pom = 0;
    for (double i = danex[0]; i <= danex[4]; i += h) //zaczynamy od pierwszego elementu z tablicy i lecimy do ostatniego co krok interpolowania
    {
        interpolowanex[pom] = i;
        interpolowaney[pom] = lagrange(danex, daney, 5, i); //interpoluje warto�� y(i) na podstawie warto�ci wprowadzeonej na pocz�tku
    }
    //2. zapisa� do pliku, dwie kolumny
    FILE* f;
    f = fopen("interpol.txt", "w");
    fprintf(f, "x\ty\n"); //nag��wek pliku
    for (int i = 0; i < ilekrok�w;i++)
    {
        fprintf(f,"%lf\t%lf\n", interpolowanex[i], interpolowaney[i]); //drukowanie do pliku po tabulatorku
    }
     fclose(f);
     //3. Wyznaczy� warto�� ca�ki oznaczonej z przedzia�u od O do 3 dla funkcji wygenerowanej w punkcie 2 (z krokiem h = O.025), wynik dzia�ania wy�wietl na ekranie
     double wartcalki = trapez(danex[0], danex[4], funkcjazinterpolowana, ilekrok�w);
     //4. Wyznaczy� miejsce zerowe funkcji przybli�onej danymi z dok�adno�ci� do 10 - 4, ilo�� iteracji wy�wietl na ekranie(4 pkt)
     int iter = 0;
     

    return 0;
}
