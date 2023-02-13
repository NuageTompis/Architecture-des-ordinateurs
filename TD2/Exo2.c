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
    for(int try=0;try<tries;try++){
        tic = __rdtscp(&ui);
        sum=0;
        for (int i=1; i <= n; i++)
            sum += i*i;
        toc = __rdtscp(&ui);
        time[try] = toc-tic;
    }

    printf("Mean of cycles for n=%d : %d\n",n,mean(time,tries));

    return 0;
}
