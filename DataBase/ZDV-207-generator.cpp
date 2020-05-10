//
//  ZDV-207-generator.cpp
//  DataBase
//
//  Created by Daniil Zakharov on 12.04.2020.
//  Copyright © 2020 Daniil Zakharov. All rights reserved.
//

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "ZDV-207-generator.h"
#define N 4096

char **wordcpy(FILE *fin, int &num)
{
    char **w;
    w = (char**)malloc(N*sizeof(char*));
    char s[N];
    int i;
    for(i=0;(i<N)&&(fscanf(fin,"%s",s)==1);i++)
    {
        w[i]=(char*)malloc(50);
        strcpy(w[i],s);
       // printf(w[i]);
        num++;
    }
    return w;
}

void printString(FILE *fout, char **w1, char **w2, char **w3, char **w4, int &num)
{
    int i,j,k,y;
    y=0;
    for (i=0; i<num * 7; i++) {
        fprintf(fout, "%s   ", w1[i]);
        fprintf(fout, "%s   ", w2[i]);
        fprintf(fout, "Предмет: ");
        fprintf(fout, "%s   ", w3[i]);
        fprintf(fout, "Дата: ");
        fprintf(fout, "%s   ", w4[i]);
        fprintf(fout, "Студенты: ");
        k = rand() % 10;
        for (j=i+1; j<=i+k; j++) {
            fprintf(fout, "%s ", w2[j]);
        }
        i = j+1;
        y++;
        fprintf(fout, "\n");
    }
    num = y;
}

char **wordrand(char **w, int num, int size)
{
    char **r;
    size = size * 7 ;
    r = (char**)malloc(size*sizeof(char*));
    int i,j;
    for (i=0; i<size; i++) {
        r[i]=(char*)malloc(50);
        j= rand() % num;
        strcpy(r[i], w[j]);
    }
    
    return r;
}

char **stringcopy(FILE *fin,int size)
{
    char **w;
    w = (char**)malloc(size*sizeof(char*));
    int i=0;
    w[i]=(char*)malloc(350);
    while (fgets(w[i], 350, fin))
       {
           i++;
           w[i]=(char*)malloc(350);
       }
    return w;
}
