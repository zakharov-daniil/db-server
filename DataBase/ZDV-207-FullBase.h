//
//  FullBase.h
//  DataBase
//  Zakharov Daniil Vadimovich 207 gr.
//
//  Created by Daniil Zakharov on 25.03.2020.
//  Copyright © 2020 Daniil Zakharov. All rights reserved.
//

#ifndef FullBase_h
#define FullBase_h
#include <iostream>
#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include "ZDV-207-classbase.h"
#include <mutex>

class base {
private:
    record *records;
    int size;

    
    
    std::mutex readmux;
    //locks when read
    std::mutex writemux;
    //locks on write
    
public:
    struct index{
        int len;
        int * vals;
        
        int& operator[](int arg){
            return vals[arg];
        }
        
        index(int size){
            len = size;
            vals = (int*)malloc(sizeof(int)*size);
        }
        ~index(){
            if(vals)
            free(vals);
        }
        
        index(const index & rhs){
            len = rhs.len;
            vals =(int*)malloc(sizeof(int)*len);
            memcpy(vals, rhs.vals, sizeof(int)*len);
        }
        index(index && rhs){
            len = rhs.len;
            vals = rhs.vals;
            rhs.vals = 0;
        }
        void operator=(const index & rhs){
            if(vals)
                free(vals);
			len = rhs.len;
            vals =(int*)malloc(sizeof(int)*len);
            memcpy(vals, rhs.vals, sizeof(int)*len);
        }
		
		void operator=(index && rhs){
			if(vals)
			free(vals);
			len = rhs.len;
            vals = rhs.vals;
            rhs.vals = 0;
		}
		
        
    };
private:
    index global;
public:
    base():global(0) {
        records = NULL;
        size = 0;
        
    }
    
    int getsize() {
        return size;
    }
    
    record getindexrecord(int i, index idx) {
        int k = idx[i];
        return records[k];
    }
    
    /*void renewindex(int sizew) {
        free(index);
        size = sizew;
        index = (int*)malloc((size)*sizeof(int));
        for (int i=0; i<size; i++) {
            index[i] = i ;
        }
    }*/
    
    void makebase(FILE *fout, int sizew);
    
    void printall(FILE *f, index idx) { // Распечатка
        readmux.try_lock();
        writemux.lock();
		for (int i=0; i<idx.len; i++) {
            records[idx[i]].printrecord(f);
        }
        readmux.unlock();
        writemux.unlock();
    }
    
    // Здесь и ниже ВЫБОРКИ
    
    // Из ТЕХНИЧЕСКИХ selectdate, selectsubject, selectlector, selectstudent, комментарии только в первой, остальные абсолютно аналогичны
    
    index selectdate(char * dat, index  );
    
    index selectsubject(char * subj, index );
    
    index selectlector(char * lectname, char * lectsurname, index );
    
    index selectstudent(char * student, index);
    
    // ПОЛНАЯ ВЫБОРКА с учетом ЛЕКСИКОГРАФИЧЕСКИХ ПРАВИЛ
    
    index selectall (char * com );
    
    void addrecord(char * com);
    
    void offrecord(char * com );
};

#endif /* FullBase_h */
