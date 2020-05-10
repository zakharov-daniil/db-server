//
//  tasker.h
//  DataBase
//
//  Created by Daniil Zakharov on 10.03.2020.
//  Copyright © 2020 Daniil Zakharov. All rights reserved.
//

#ifndef tasker_h
#define tasker_h
#include <iostream>
#include "stdio.h"
#include <stdlib.h>
#include <string>



char **addstring(FILE *fin, char **w, int sizew, int sizef)
{
    char **add, **total;
    add = stringcopy(fin, sizef);
    int i, size = sizef + sizew;
    total = (char**)malloc(size*sizeof(char*));
    for (i=0; i < sizew ; i++) {
        total[i]=(char*)malloc(350);
        strcpy(total[i], w[i]);
       // free(w[i]);
    }
    for (i=sizew; i<size; i++) {
        total[i]=(char*)malloc(350);
        strcpy(total[i], add[i-sizew]);
      //  free(add[i]);
    }
    return total;
}

void deletestring(char **w, int size, char *com)
{
    int i=0;
    for (i=0; i<size; i++) {
        if (strstr(w[i], com)) {
            free(w[i]);
        }
    }
}

void printarray(char **w, int size)
{
    int i;
    for (i=0; i<size; i++) {
        if (w[i]) {
            printf("%s\n",w[i]);
        }
    }
}


void printarrayint(char **w, int *a, int size)
{
    int i,k;
    for (i=0; i<size; i++) {
        k=a[i];
        if (w[k]) {
            printf("%s\n",w[k]);
        }
        if (!a[i+1]) {
            break;
        }
    }
}

int * listsurn(char *com, char **w, int sizew, int *n)
{
    int i,j=0,k=0;
    int a[sizew];
    char *p;
    for (i=0; i<sizew; i++) {
        k = n[i];
        p = strstr(w[k], "Студенты:");
        if (p && (strstr(p, com))) {
            a[j]=k;
            j++;
        }
        if (!n[i+1]) {
            break;
        }
    }
    int *b = (int *)malloc((j)*sizeof(int));
    for (i=0; i<j; i++) {
        b[i] = a[i];
    }
    free(n);
    return b;
}

/*int * listsurn(char *com, record *rec, int size, int *n)
{
    int i,j=0,k=0;
    int a[size];
    for (i=0; i<size; i++) {
        k = n[i];
        if (p && (strstr(p, com))) {
            a[j]=k;
            j++;
        }
        if (!n[i+1]) {
            break;
        }
    }
    int *b = (int *)malloc((j)*sizeof(int));
    for (i=0; i<j; i++) {
        b[i] = a[i];
    }
    free(n);
    return b;
}*/

int *listdate(char *com, char **w, int sizew, int *n)
{
    int i,j=0,k=0;
    int a[sizew];
    char *p;
    for (i=0; i<sizew; i++) {
        k = n[i];
        p = strstr(w[k], "Дата:");
        if (p && (strstr(p, com))) {
            a[j]=k;
            j++;
        }
        if (!n[i+1]) {
            break;
        }
    }
    int *b = (int *)malloc((j)*sizeof(int));
    for (i=0; i<j; i++) {
        b[i] = a[i];
    }
    free(n);
    return b;
}

int *listsubj(char *com, char **w, int sizew, int *n)
{
    int i,j=0,k=0;
    int a[sizew];
    char *p;
    for (i=0; i<sizew; i++) {
        k = n[i];
        p = strstr(w[k], "Предмет:");
        if (p && (strstr(p, com))) {
            a[j]=k;
            j++;
        }
        if (!n[i+1]) {
            break;
        }
    }
    int *b = (int *)malloc((j)*sizeof(int));
    for (i=0; i<j; i++) {
        b[i] = a[i];
    }
    free(n);
    return b;
}

int *listlect(char *com, char **w,int sizew,int *n)
{
    int i,j=0,k=0;
    int a[sizew];
    for (i=0; i<sizew; i++) {
        k = n[i];
        if ((strstr(w[k], com))) {
            a[j]=k;
            j++;
        }
        if (!n[i+1]) {
            break;
        }
    }
    int *b = (int *)malloc((j)*sizeof(int));
    for (i=0; i<j; i++) {
        b[i] = a[i];
    }
    free(n);
    return b;
}

/* ~record() {
       if(namelect) {
           free(namelect);
           namelect = 0;
       }
       if(surnlect) {
           free(surnlect);
           surnlect = 0;
       }
       if(date) {
           free(date);
           date = 0;
       }
       if(subject) {
           free(subject);
           subject = 0;
       }
       for (int i=0; i<10; i++) {
           if (students[i]) {
               free(students[i]);
               students[i] = 0;
           }
       }
   }*/



#endif /* tasker_h */
