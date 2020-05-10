//
//  server.hpp
//  DataBase
//  Zakharov Daniil Vadimovich 207 gr.
//
//  Created by Daniil Zakharov on 23.04.2020.
//  Copyright © 2020 Daniil Zakharov. All rights reserved.
//

#ifndef server_hpp
#define server_hpp

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>  /* Needed for getaddrinfo() and freeaddrinfo() */
#include <unistd.h> /* Needed for close() */
#include "ZDV-207-FullBase.h"
#include "ZDV-207-classbase.h"

extern int serv_fd;
extern base b;

typedef struct { //Общая структура для подключенного клиента
    char query[2048]; //тут будет то, что он прислал
    int client_fd;    //тут номер клиента
    FILE * fclient;   //файл с результатом работы сервера, отсылается клиенту в результате работы
} conn_t;


void init_server(int portno); //Инициализация сервера
conn_t get_client(void);      //И клиента
void process (conn_t connection); //Происходящий процесс, на 4 этапе - выборка


#endif /* server_hpp */
