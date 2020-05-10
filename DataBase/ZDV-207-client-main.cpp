//
//  main.cpp
//  client
//
//  Created by Daniil Zakharov on 23.04.2020.
//  Copyright © 2020 Daniil Zakharov. All rights reserved.
//

#include <iostream>
#include "ZDV-207-client.h"
int main() {
    
    FILE * fin = fopen("command.txt", "r"); //Отсюда берём команды
    FILE * fout = fopen("result.txt", "w"); //Сюда будем писать ответ сервера
    //FILE *client;
    char cmbuf [4096];                      //Этим перечитываем строки-команды из fin
    char rdbuf [4096];                      //Этим перечитываем ответ сервера (построчно)
    while (fgets(cmbuf, 4095, fin)) {
        cmbuf[strlen(cmbuf)-1]=0;           //Уберём символ перехода строки, иначе плохо
        FILE * client = Client::request(cmbuf, "127.0.0.1", 3228); // Получаем ответ сервера
        while (fgets(rdbuf, 4095, client)) {
            fprintf(fout, "%s", rdbuf);      //Печатаем ответ
        }
    }
    

    
    
    return 0;
}
