#include <stdio.h>
#include <x86intrin.h>

void acces_seq(int n)
{
    int *TAB;
    TAB = malloc(sizeof(int) * 10000000);
    for (int i = 0; i < n; i++)
    {
        TAB[i] = i;
    }
    free(TAB);
}

void acces_alea(int n)
{
    int *TAB;
    TAB = malloc(sizeof(int) * 10000000);
    for (int i = 0; i < n; i++)
    {
        TAB[rand() % n] = i;
    }
    free(TAB);
}

void print_timing(int mon_arg, void (*ma_fonction)(int), int nombre_init, int nombre_iter)
{

    // init
    unsigned int ui;
    for (int i = 0; i < nombre_init; i++)
    {
        __rdtscp(&ui);
    }
    ////

    // calcul

    unsigned long int *tab;
    tab = malloc(nombre_iter * sizeof(unsigned long int));

    unsigned long int tic, toc;
    for (int i = 0; i < nombre_iter; i++)
    {
        unsigned int ui;

        tic = __rdtscp(&ui);
        ma_fonction(mon_arg);
        toc = __rdtscp(&ui);

        tab[i] = toc - tic;
    }
    ////

    // moyenne

    unsigned long int moyenne = 0;

    for (int i = 0; i < nombre_iter; i++)
    {
        moyenne += tab[i];
    }
    moyenne = moyenne / nombre_iter;
    ////

    printf("time spent : %lu\n", moyenne);
}

void main()
{
    int n = 10000;

    print_timing(n, acces_seq, 5, 10);
    print_timing(n, acces_alea, 5, 10);
}
