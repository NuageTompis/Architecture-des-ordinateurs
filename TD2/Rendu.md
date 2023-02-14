# Compte-rendu séance 2

## Exercice 1
  >***Sur l'ordinateur de Simon***

  **a)** En exécutant la fonction main d’un script C la machine de Simon peut allouer au maximum environ **8370000** octets dans la pile correspondante (script ReachStackLimit.c)
Le programme retourne l’erreur Segmentation fault si on essaie d’allouer trop d’octets dans la pile (par exemple **8380000**).

>**Notes :** *L’arithmétique des pointeurs*, c’est la façon dont on incrémente les pointeurs. Par exemple en c, si on déclare la variable p comme un pointeur vers un tableau d’entiers, alors lorsqu’on appelle p++ cela incrémente p de 4 car c’est la taille en octets d’un entier.

  **b)** C’est donc 10^7 octets.
  
  **c)** Sur la machine de Simon il est par exemple possible d’allouer 10^10 octets sur le tas mais pas 10^11.

  **d)** Chacune de nos machine utlise la convention little-endian
  
  **e)** Les lignes qui composent le tableau tridimensionnel sont juxtaposées les une après les autres : on a donc tab[0][0][0] -> tab[0][0][9], puis tab[0][1][0] -> tab[0][1][9], jusqu'à tab[9][9][0] -> tab[9][9][9].

<br/>

## Exercice 2
```
#include<stdio.h>
#include <x86intrin.h>

#define n 100000
#define tries 10

int mean(int* p, int size){
    int sum = 0;
    for(int i = 0;i<size;i++,p++){
        sum+=*p;
    }
    return sum/size;
}

int main(){
    unsigned long int tic,toc;
    unsigned int ui;
    tic = __rdtscp(&ui);
    tic = __rdtscp(&ui);
    tic = __rdtscp(&ui);
    tic = __rdtscp(&ui);
    tic = __rdtscp(&ui);

    int sum;
    int time[tries];
    for(int try=0 ; try<tries ; try++){
        tic = __rdtscp(&ui);
        sum=0;
        for (int i=1; i <= n; i++)
            sum += i * i;
        toc = __rdtscp(&ui);
        time[try] = toc-tic;
    }

    printf("Mean of cycles for n=%d : %d\n", n, mean(time,tries));

    return 0;
}
```

<br/>

 Les valeurs obtenues sont :
|  n      | 1000   | 10000 | 1000000 | 10000000 | 100000000 |
|:--------|--------|-------|---------|----------|-----------|
| mesure  | 9034   | 87931 | 888774  | 9083605  | 688093670 |


<br/>

```
#include <stdio.h>
#include <x86intrin.h>

void acces_seq(int n)
{
    int *TAB;
    TAB = malloc(sizeof(int) * 1000000000);
    for (int i = 0; i < n; i++)
    {
        TAB[i] = i;
    }
}

void acces_alea(int n)
{
    int *TAB;
    TAB = malloc(sizeof(int) * 100000);
    for (int i = 0; i < n; i++)
    {
        if (i / 100 == 0)
        {
            printf("Done %d percent\n", 100 * i / n);
        }

        TAB[rand()] = i;
    }
}

void print_timing(int mon_arg, void (*ma_fonction)(int), int nombre_init, int nombre_iter)
{ 
  ...
}

void main()
{
    int n = 1000000;

    print_timing(n, acces_seq, 5, 10);
    print_timing(n, acces_alea, 5, 10);
}
```

## Exercice 3
```
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
```

<br/>


## Exercice 4


<br/>

 Les valeurs obtenues sont :
|  n      | 10000   | 10^6 | 10^7 | 10^8 | 10^9 |
|:--------|--------|-------|---------|----------|-----------|
| seq  | 9034   | 87931 | 888774  | 9083605  | 688093670 |
| alea  | 9034   | 87931 | 888774  | 9083605  | 688093670 |


<br/>


<br/>


## Exercice 5

```
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
```






