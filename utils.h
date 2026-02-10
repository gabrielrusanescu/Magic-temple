#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

int palindrom(int n)
{
    if(n<0)
        return 0;
    int invers=0,original=n;
    while(n)
    {
        invers=invers*10+n%10;
        n/=10;
    }
    if(invers==original)
        return 1;
    return 0;
}

int prim(int n)
{
    if(n<=1)
        return 0;
    else if(n==2)
        return 1;
    else if(n%2==0)
        return 0;
    for(int d=3; d*d<=n; d+=2){
        if(n%d==0)
            return 0;
    }
    return 1;
}

int maxi(int a, int b)
{
    if(a>=b) return a;
    return b;
}

void SolveTask1();
void SolveTask2();
void SolveTask3();

