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
//mamy dane, wprowadŸmy je - talbice bêd¹ 5cioelementowe statyczne na pocz¹tku, bo tak¹ mamy tabelkê
int N = 5;
/* //dla danych stacjonarnie pobranych
double danex[5] = { -1.0,0.0,1.0,2.0,3.0 }; //double, ¿eby siê dobrze mno¿y³o
double daney[5] = { -2.5,-1.5,-1,0.25,0.75 }; //liczby z kropk¹
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

    //zak³adam, ¿e na pocz¹tku pliku podana jest liczba punktów
    fclose(plik);
}

double funkcjazinterpolowana(double x) //do 3.
{
    return lagrange(danex, daney, 5, x);
}
int main()
{
    //mamy dane, wprowadŸmy je - talbice bêd¹ 5cioelementowe statyczne na pocz¹tku, bo tak¹ mamy tabelkê
    danezpliku();

    //1. Przeprowadziæ interpolacjê danych z krokiem h - 0.025
    double h = 0.025;

    //tu mo¿na na kilka sposobów, zobaczymy
    //sprawdzamy, ile bêdzie potrzebne kroków
    //pobranie danych z pliku
    int ilekroków =(int)(danex[4] - danex[0])/h; //ofc elementy tablicy liczy siê od 0; dzielimy szerokoœæ dziedziny na krok i mamy ile kroków musimy przejœc
    double* interpolowanex = (double *)malloc(ilekroków*sizeof(double));
    double* interpolowaney = (double *)malloc(ilekroków*sizeof(double));
    int pom = 0;
    for (double i = danex[0]; i <= danex[4]; i += h) //zaczynamy od pierwszego elementu z tablicy i lecimy do ostatniego co krok interpolowania
    {
        interpolowanex[pom] = i;
        interpolowaney[pom] = lagrange(danex, daney, 5, i); //interpoluje wartoœæ y(i) na podstawie wartoœci wprowadzeonej na pocz¹tku
        pom++
    }
    //2. zapisaæ do pliku, dwie kolumny
    FILE* f;
    f = fopen("interpol.txt", "w");
    fprintf(f, "x\ty\n"); //nag³ówek pliku
    for (int i = 0; i < ilekroków;i++)
    {
        fprintf(f,"%.5f\t%.5f\n", interpolowanex[i], interpolowaney[i]); //drukowanie do pliku po tabulatorku. .5f to 5 miejsc po przecinku
    }
    fclose(f);
    //3. Wyznaczyæ wartoœæ ca³ki oznaczonej z przedzia³u od O do 3 dla funkcji wygenerowanej w punkcie 2 (z krokiem h = O.025), wynik dzia³ania wyœwietl na ekranie
    double wartcalki = trapez(danex[0], danex[4], funkcjazinterpolowana, ilekroków);
    //4. Wyznaczyæ miejsce zerowe funkcji przybli¿onej danymi z dok³adnoœci¹ do 10 ^- 4, iloœæ iteracji wyœwietl na ekranie(4 pkt)
    int iter = 0;
    double epsilon = 0.0001;
    double mz = 0; //na miejsce zerowe
    mz = bisec(danex[0], danex[4], funkcjazinterpolowana, epsilon, &iter); //wartoœci funkcji na poczatku sa -, potem + _ musi byc miejsce zerowe pomiedzy. skorzystamy z bisekcji
    printf("\nMiejscezerowe = %.4f, liczba iteracji bisekcji = %d", mz, iter);

    free(interpolowanex);
    free(interpolowaney);
    free(danex);
    free(daney);
    return 0;
}
