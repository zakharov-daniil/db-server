//
//  classbase.h
//  DataBase
//  Zakharov Daniil Vadimovich 207 gr.
//
//  Created by Daniil Zakharov on 25.03.2020.
//  Copyright © 2020 Daniil Zakharov. All rights reserved.
//

#ifndef classbase_h
#define classbase_h
#include <iostream>
#include "stdio.h"
#include <stdlib.h>
#include <string.h>

class record {
private:
    char *namelect;
    char *surnlect;
    char *date;
    char *subject;
    char * students[10];
    int length;
public:
    record() {
        length = 0;
        namelect = NULL;
        surnlect = NULL;
        date = NULL;
        subject = NULL;
        //students = NULL;
        for (int i =0; i<10; i++) {
            students[i]= NULL;
        }
    }
    
    
    record& operator= (const record &rec) {
        namelect = strdup(rec.getnamelect());
        surnlect = strdup(rec.getsurnlect());
        date = strdup(rec.getdate());
        subject = strdup(rec.getsubject());
        for (int i=0; i<10; i++) {
            if (rec.getstudents(i)) {
                students[i] = strdup(rec.getstudents(i));
            }
        }
        return *this;
    }
    
    char * getnamelect() const {
        return namelect ;
    }
    char * getsurnlect() const {
        return surnlect;
    }
    char * getdate() const {
        return date;
    }
    char * getsubject() const {
        return subject;
    }
    char * getstudents(int i) const {
        return students[i];
    }
    int getLength() const {
        return length;
    }
    
    void makerecord(char * w);
    
    
    
    void printrecord(FILE *f = stdout);
};
 


#endif /* classbase_h */
