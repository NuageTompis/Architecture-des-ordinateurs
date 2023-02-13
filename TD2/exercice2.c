#include <x86intrin.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

unsigned long int test(int MAX){
    unsigned long tic,toc;
    unsigned int ui;
    unsigned long int a;
    tic = __rdtscp(&ui);
    for (int i=0; i<MAX; i++){
        a = a*a;
    }
    toc = __rdtscp(&ui);
    return toc-tic;
}

unsigned long int average(int MAX){
    unsigned long int tab[10];
    unsigned long int ret = 0;
    for (int i=0; i<10; i++){
        if (i>=4){
            ret+=test(MAX);
        }
    }
    return (unsigned long int)(ret/5);
}

int main(){
    int* tab;
    int ret;
    tab = malloc(6*sizeof(int));
    for (int i=1000; i<pow(10,9); i=i*10){
        ret = (int)average(i);
        printf("pour %d ",i);
        printf("la moyenne est %d \n", ret);
    }
}