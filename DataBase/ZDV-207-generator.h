//
//  generator.h
//  DataBase
//  Zakharov Daniil Vadimovich 207 gr.
//
//  Created by Daniil Zakharov on 24.02.2020.
//  Copyright © 2020 Daniil Zakharov. All rights reserved.
//

#ifndef generator_h
#define generator_h
#include <iostream>
#include <string.h>
#include <stdlib.h>

#define N 4096

char **wordcpy(FILE *fin, int &num);

void printString(FILE *fout, char **w1, char **w2, char **w3, char **w4, int &num);

char **wordrand(char **w, int num, int size);

char **stringcopy(FILE *fin,int size);

#endif /* generator_h */
