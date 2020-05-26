//
//  ZDV-207-FullBase.cpp
//  DataBase
//
//  Created by Daniil Zakharov on 12.04.2020.
//  Copyright © 2020 Daniil Zakharov. All rights reserved.
//

#include <stdio.h>
#include "ZDV-207-generator.h"
#include "ZDV-207-classbase.h"
#include "ZDV-207-FullBase.h"

void base:: makebase(FILE *fout, int sizew) {
    char ** w;
    size = sizew;
    w = stringcopy(fout, size); // Файл раздирается на строки, эта функция есть в generator.h
    
    
    records = new record[size]; // Создается массив записей типа record
    for (int i = 0; i<size; i++) {
        records[i].makerecord(w[i]); // Каждая строка переводится в тип record -- описание см. в classbase.h
    }
    
    global = index(size);
    for(int i =0; i < size; i++){
        global[i] = i;
    }
    
    free(w);
}

base::index base:: selectdate(char * dat, index ind) {
    int i,k=0,j=0;
    index newindex(ind.len);
    char *p;
    
    for (i = 0; i < ind.len; i++) {
        k = ind[i]; // Проходим по значениям уже данной выборки ind
        p = records[k].getdate();
        if (strcmp(p, dat)==0) { // Если параметр совпал, то добавляем старый индекс в новый массив
            newindex[j] = k;
            j++;
        }
    }
    newindex.len = j;
    return (newindex);
}

base::index base::selectsubject(char * subj, index ind) {
    int i,k=0,j=0;
    index newindex(ind.len);
    char *p;
    
    for (i = 0; i < ind.len; i++) {
        k = ind[i];
        p = records[k].getsubject();
        if (strcmp(p, subj)==0) {
            newindex[j] = k;
            j++;
        }
    }
    newindex.len = j;
    return newindex;
}

base::index base:: selectlector(char * lectname, char * lectsurname, index ind ) {
    int i,k=0,j=0;
    index newindex(ind.len);
    char *p1, *p2;
    
    for (i = 0; i < ind.len ; i++) {
        k = ind[i];
        p1 = records[k].getnamelect();
        p2 = records[k].getsurnlect();
        if ((strcmp(p1, lectname) == 0 ) && (strcmp(p2, lectsurname) == 0 )) {
            newindex[j] = k;
            j++;
        }
    }
    newindex.len = j;
    return newindex;
}

base::index base:: selectstudent(char * student, index ind) {
    int i,k=0,j=0,a=0;
    index newindex(ind.len);
    char *p;
    
    for (i = 0; i < ind.len; i++) {
        k = ind[i];
        for (a=0; a<10; a++) {
            p = records[k].getstudents(a);
            if ( p ) {
                 if (strcmp(p, student)==0) {
                    newindex[j] = k;
                    j++;
                 }
            }
        }
    }
    newindex.len = j;
    return newindex;
}

base::index base:: selectall (char * com ) {
    int num = 0; // индекс последнего слова
    char *q[18];
    int i;
    if (strncmp(com, "select*", 5) == 0) { // Проверка что делать -- здесь на именно выбор
        q[0] = strtok(com, " ");
        
        for(i=1;(i<11);i++)
        {
            q[i] = strtok(NULL, " ");
        }
        for (num=0; num<11; num++) {
            //printf("%s\n",q[num]);
            if (!q[num+1]) {
                break;
            }
        }
        if (num == 11) {
            num--;
        }
        readmux.try_lock(); //может быть 2 чтения одновременно
        writemux.lock();
        // ВЫБОР -- по каждому параметру
        index idx(global);
        for (i=0; i<num; i++) {
            if (strcmp(q[i], "subject=") == 0) {
                idx = selectsubject(q[i+1], idx);
            }
            if (strcmp(q[i], "date=") == 0) {
                idx = selectdate(q[i+1], idx);
            }
            if (strcmp(q[i], "student=") == 0) {
                idx = selectstudent(q[i+1], idx);
            }
            if (strcmp(q[i], "lector=") == 0) {
                idx = selectlector(q[i+1], q[i+2], idx);
            }
        }
        readmux.unlock(); //операция завершена, можно писать
        writemux.unlock();
        return idx;
    }
    
    if (strncmp(com, "add*",3) == 0) { // Здесь -- проверка на необходимость добавления
        char *com2 =(char*)malloc(300) ;
        q[0] = strtok(com, " ");
        for(i=1;(i<18);i++)
        {
            q[i] = strtok(NULL, " ");
        }
        for (num=0; num<19; num++) {
            if (!q[num+1]) {
                break;
            }
        }
        for (i=1; i<=num; i++) { // Из командной строки конструируется необходимая для добавления
            strcat(com2, q[i]);
            strcat(com2, " ");
        }
        writemux.lock();
        readmux.lock();
        //printf("%s\n",com2);
        addrecord(com2); // Добавление нужной строки
        writemux.unlock();
        readmux.unlock();
    }
    if (strncmp(com, "delete*",6) == 0) { // Здесь -- проверка на необходимость удаления
        char *com3 =(char*)malloc(300) ;
        q[0] = strtok(com, " ");
        for(i=1;(i<18);i++)
        {
            q[i] = strtok(NULL, " ");
        }
        for (num=0; num<19; num++) {
            if (!q[num+1]) {
                break;
            }
        }
        for (i=1; i<=num; i++) { // Из командной строки конструируется необходимая для удаления
            strcat(com3, q[i]);
            strcat(com3, " ");
        }
        //printf("%s\n",com3);
        writemux.lock();
        readmux.lock();
        offrecord(com3); // Удаление нужной строки
        writemux.unlock();
        readmux.unlock();
    }
    return index(0);
}

void base:: addrecord(char * com) {
    record *new_records;
    new_records = new record[size+1];
    for (int i=0; i<size; i++) { // Создание нового массива записей
        new_records[i] = records[i];
      //  new_records[i].printrecord();
    }
    new_records[size].makerecord(com); // В последнюю запись -- добавить новую
    //new_records[size].printrecord();
    size++;
    delete records;
    records = new_records;
    
    index idx(size); // нужно синхронизировать глобальный массив индексов
    for (int i=0; i<size-1; i++) {
        idx[i] = global[i];
    }
    idx[size-1] = size;
    global = idx;

}

void base:: offrecord(char * com) {
    int num = 0;
    int j=0,k=0,i=0,t=0,u=0;
    record p;
    p.makerecord(com);
    for (u=0; u<size; u++) { // Тупо проверка по всем параметрам и удаление, если всё совпало
        i = global[u];
        if (strcmp(records[i].getnamelect(), p.getnamelect())==0){
            if (strcmp(records[i].getsurnlect(), p.getsurnlect())==0) {
                if (strcmp(records[i].getdate(), p.getdate())==0) {
                    if (strcmp(records[i].getsubject(), p.getsubject())==0) {
                        for ( j=0; j<10; j++) {
                            for ( k=0; k<10; k++) {
                                if (p.getstudents(k) && records[i].getstudents(j)) {
                                    if (strcmp(records[i].getstudents(j), p.getstudents(k))==0) {
                                        num++;
                                    }
                                    if (!p.getstudents(k+1)) {
                                        break;
                                    }
                                }
                                if (!p.getstudents(j+1)) {
                                    break;
                                }
                            }
                        }
                        if ( (num == j)&&(j == k) ) {
                            t = u;
                            records[i].~record();
                        }
                    }
                }
            }
        }
        
    }
    size--;
    
    index idx(size); // нужно синхронизировать глобальный массив индексов
    for (int i=0; i<size-1; i++) {
        idx[i] = global[i];
    }
    idx[size-1] = size;
    global = idx;
 
    //renewindex(size);
}
