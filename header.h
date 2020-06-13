#ifndef __HEADER
#define __HEADER


struct sub_array {
	int * begin;
	int * end;
};


typedef struct sub_array sub_array;

double drand(void);
int random_range(int pocz, int kon);
void wypelnij_tablice_los(int *tab, int rozmiar, int min, int max);
long long suma_elem(int tab[], int rozmiar);
void wyswietl(int tablica[], int rozmiar);



#endif // __HEADER
