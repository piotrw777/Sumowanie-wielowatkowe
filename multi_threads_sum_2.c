#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include "header.h"

#define MIN_V -1001  // dolna granica wartości elementu tablicy
#define MAX_V 1000   // górna granica wartości elementu tablicy

int i = 0;

void *threadFunction(void * arg) {
     int suma = 0;
     i++;
     sub_array *wsk_sa = (sub_array *) arg;
     int *wsk = wsk_sa->begin;
     //sumujemy w przedziale [*begin, *end)
     do {
        suma += *wsk++;
     } while(wsk != wsk_sa->end);
     printf("Jestem watkiem nr %d o id: %ld\n", i, pthread_self());
     printf("Odebralem argumenty: %d %d\n",(void *)(wsk_sa->begin), (void *) (wsk_sa->end) );
     printf("Suma podtablicy to: %d\n\n", suma);
     return (void *) suma;
}

int main(void) {
    int M;
    int ROZMIAR;

    printf("Podaj rozmiar tablicy: ");
    scanf("%d", &ROZMIAR);

    printf("Podaj ilość wątków: ");
    scanf("%d", &M);

    pthread_t *w = (pthread_t *) malloc(M * sizeof(pthread_t)); //wątki
    int *res = (int *) malloc(M * sizeof(int));
    long long S_thr = 0; //suma obliczana przez wątki
    long long S_wer = 0; // suma obliczana standardowo
    int *S = (int *) malloc(M * sizeof(int)); //tablica dla sum obliczanych przez wątki
    sub_array *sa = (sub_array *) malloc(M * sizeof(sub_array));   //argumenty dla wątków
    int sa_size = ROZMIAR / M + (int) (2*(ROZMIAR % M) > M); //rozmiar podtablicy przesyłanej do wątków
    int *tab = (int *) malloc(ROZMIAR * sizeof(int)); //główna tablica
    int k;          //licznik;

    //wypełniamy tablicę
    srand(time(0));
    wypelnij_tablice_los(tab, ROZMIAR, MIN_V, MAX_V);

    //wyswietl(tab, ROZMIAR);

    //liczymy sumę elementów tablicy
    S_wer = suma_elem(tab, ROZMIAR);

    printf("Suma elementów tablicy to: %lld\n", S_wer);
    printf("Ilość wątków: %d\n", M);
    printf("Rozmiar podtablicy: %d\n", sa_size);

    for(k = 0; k < M - 1; k++) {
        sa[k].begin = tab + k * sa_size;
        sa[k].end = sa[k].begin + sa_size;
    }
    sa[M - 1].begin = tab + (M - 1)*sa_size;
    sa[M - 1].end = tab + ROZMIAR;
    //tworzenie wątków
    for(k = 0; k < M; k++) {
        res[k] = pthread_create(&w[k], NULL, &threadFunction, &sa[k]);
        if(res[k] != 0) {
            printf("Błąd wątku %d", k);
            exit(k);
        }
    }
    //czekamy na wątki
    for(k = 0; k < M; k++) {
        pthread_join(w[k], (void *) &S[k]);
    }

    //sumujemy wyniki zwrócone przez  wątki
    for(k = 0; k < M; k++) {
        S_thr += S[k];
    }
    printf("Suma obliczona przez wątki: %lld\n",S_thr);
    printf("Suma obliczona standardowo: %lld\n",S_wer);
    printf("%s",(S_thr == S_wer) ? "Suma się zgadza\n" : "Sumy są różne\n");

    //zwalnianie pamięci
    free(w);
    free(res);
    free(sa);
    free(S);
    free(tab);

}

