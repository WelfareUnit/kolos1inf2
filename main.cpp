#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "gauss.h"
#include "inter.h"
#include "kwad.h"
#include "rk4.h"
#include "nonlin.h"
//#include "winbgi2.h"
//mamy dane, wprowad�my je - talbice b�d� 5cioelementowe statyczne na pocz�tku, bo tak� mamy tabelk�
int N = 5;
/* //dla danych stacjonarnie pobranych
double danex[5] = { -1.0,0.0,1.0,2.0,3.0 }; //double, �eby si� dobrze mno�y�o
double daney[5] = { -2.5,-1.5,-1,0.25,0.75 }; //liczby z kropk�
*/
//dla danych z pliku
double* danex;
double* daney;
void danezpliku()
{
    FILE* plik = fopen("init.txt", "r");
    if (plik == NULL)
    {
        printf("Blad otwarcia pliku!\n");  // drukujemy komunikat o bledzie
        exit(1);
    }
    daney = (double*)malloc(N * sizeof(double));
    danex = (double*)malloc(N * sizeof(double));
    fscanf(plik, "%d", &N);
    for (int i = 0; i < N; i++)
    {
        fscanf(plik, "%lf\t%lf", &danex[i], &daney[i]);

    }

    //zak�adam, �e na pocz�tku pliku podana jest liczba punkt�w
    fclose(plik);
}

double funkcjazinterpolowana(double x) //do 3.
{
    return lagrange(danex, daney, 5, x);
}
int main()
{
    //mamy dane, wprowad�my je - talbice b�d� 5cioelementowe statyczne na pocz�tku, bo tak� mamy tabelk�
    danezpliku();

    //1. Przeprowadzi� interpolacj� danych z krokiem h - 0.025
    double h = 0.025;

    //tu mo�na na kilka sposob�w, zobaczymy
    //sprawdzamy, ile b�dzie potrzebne krok�w
    //pobranie danych z pliku
    int ilekrok�w =(int)(danex[4] - danex[0])/h; //ofc elementy tablicy liczy si� od 0; dzielimy szeroko�� dziedziny na krok i mamy ile krok�w musimy przej�c
    double* interpolowanex = (double *)malloc(ilekrok�w*sizeof(double));
    double* interpolowaney = (double *)malloc(ilekrok�w*sizeof(double));
    int pom = 0;
    for (double i = danex[0]; i <= danex[4]; i += h) //zaczynamy od pierwszego elementu z tablicy i lecimy do ostatniego co krok interpolowania
    {
        interpolowanex[pom] = i;
        interpolowaney[pom] = lagrange(danex, daney, 5, i); //interpoluje warto�� y(i) na podstawie warto�ci wprowadzeonej na pocz�tku
        pom++
    }
    //2. zapisa� do pliku, dwie kolumny
    FILE* f;
    f = fopen("interpol.txt", "w");
    fprintf(f, "x\ty\n"); //nag��wek pliku
    for (int i = 0; i < ilekrok�w;i++)
    {
        fprintf(f,"%.5f\t%.5f\n", interpolowanex[i], interpolowaney[i]); //drukowanie do pliku po tabulatorku. .5f to 5 miejsc po przecinku
    }
    fclose(f);
    //3. Wyznaczy� warto�� ca�ki oznaczonej z przedzia�u od O do 3 dla funkcji wygenerowanej w punkcie 2 (z krokiem h = O.025), wynik dzia�ania wy�wietl na ekranie
    double wartcalki = trapez(danex[0], danex[4], funkcjazinterpolowana, ilekrok�w);
    //4. Wyznaczy� miejsce zerowe funkcji przybli�onej danymi z dok�adno�ci� do 10 ^- 4, ilo�� iteracji wy�wietl na ekranie(4 pkt)
    int iter = 0;
    double epsilon = 0.0001;
    double mz = 0; //na miejsce zerowe
    mz = bisec(danex[0], danex[4], funkcjazinterpolowana, epsilon, &iter); //warto�ci funkcji na poczatku sa -, potem + _ musi byc miejsce zerowe pomiedzy. skorzystamy z bisekcji
    printf("\nMiejscezerowe = %.4f, liczba iteracji bisekcji = %d", mz, iter);

    free(interpolowanex);
    free(interpolowaney);
    free(danex);
    free(daney);
    return 0;
}
