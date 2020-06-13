#include <stdio.h>
#include <stdlib.h>
#include "header.h"

double drand(void) {
    double d = rand()/(double) RAND_MAX;
    return d;

}

int random_range(int pocz, int kon)  {
     int k = (kon - pocz + 1) * drand() + pocz;
     return k;
}

void wypelnij_tablice_los(int *tab, int rozmiar, int min, int max) {
    int k = 0;
    for(k = 0; k < rozmiar; k++) {
        tab[k] = random_range(min,max);
    }
}
long long suma_elem(int tab[], int rozmiar) {
    long long suma = 0;
    int k;
    for(k = 0; k < rozmiar; k++) {
        suma += tab[k];
    }
    return suma;
}

void wyswietl(int tablica[], int rozmiar) {
    int k = 0;
    for(k = 0; k < rozmiar; k++) {
        printf("%d ", tablica[k]);
    }
    printf("\n");
}

