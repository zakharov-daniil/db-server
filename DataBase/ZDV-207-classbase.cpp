//
//  ZDV-207-classbase.cpp
//  DataBase
//
//  Created by Daniil Zakharov on 12.04.2020.
//  Copyright © 2020 Daniil Zakharov. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "ZDV-207-classbase.h"

void record:: makerecord(char * w) {
    int num=0;      //индекс последнего слова
     char *q[18];   //слова в записи, их не больше 18
     int i;
     q[0] = strtok(w, " ");
     for(i=1;(i<19);i++) {
         q[i] = strtok(NULL, " ");
     }
     for (num=0; num<19; num++) {
         if (!q[num+1]) {
             break;
         }
     }
    //Загрузка записи
    namelect = q[0];
    surnlect = q[1];
    subject = q[3];
    date = q[5];
    if (num > 6) {
        //students = (char**)malloc((num)*sizeof(char*));
        for (i=7; i<=num; i++) {
            students[i-7] = (char *)malloc(40);
            strcpy(students[i-7], q[i]);
        }
    }
}

void record:: printrecord(FILE *f) {
    fprintf(f, "%s %s %s %s ",namelect,surnlect,date,subject );
    fprintf(f,"Студенты: ");
    for (int i=0; i<10; i++) {
        fprintf(f,"%s ", students[i]);
        if (!students[i+1]) {
            break;
        }
    }
    fprintf(f,"\n");
}
