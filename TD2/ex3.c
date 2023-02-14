#include <stdio.h>
#include <x86intrin.h>

void test(int a)
{
    int tab[1000];
    for (int i = 0; i < 1000; i++)
    {
        printf("aaaaoohoh");
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

    printf("time spent : %lu\n", moyenne);
}

void main()
{
    int a = 12;
    print_timing(a, test, 5, 10);
}
