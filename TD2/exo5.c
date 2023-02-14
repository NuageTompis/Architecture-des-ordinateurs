#include <stdio.h>
#include <x86intrin.h>

void exo5(int pas)
{
    int *TAB;
    int TAILLE = 10000;
    TAB = malloc(sizeof(int) * TAILLE);
    int x;
    for (int i = 0; i < 10000000; i++)
    {
        x = TAB[(i + pas) % TAILLE];
    }
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

    unsigned long int moyenne;

    for (int i = 0; i < nombre_iter; i++)
    {
        moyenne += tab[i];
    }
    moyenne = moyenne / nombre_iter;
    ////

    printf("cycles needed : %lum\n", moyenne / 1000000);
}

int main()
{
    int steps[7] = {1, 2, 3, 4, 8, 16, 32};

    for (int i = 0; i < sizeof(steps) / sizeof(int); i++)
    {
        printf("With a step of %d : ", steps[i]);
        print_timing(steps[i], exo5, 10, 10);
    }

    return 0;
}
