//
//  server.cpp
//  DataBase
//  Zakharov Daniil Vadimovich 207 gr.
//
//  Created by Daniil Zakharov on 23.04.2020.
//  Copyright © 2020 Daniil Zakharov. All rights reserved.
//

#include "ZDV-207-server.hpp"
//#include "server.h"
#include <string.h>
base b;
//static const char * okhdr = "HTTP/1.1 200 OK\r\nContent-length: %lu\r\nContent-Type: %s\r\nConnection: close\r\n\r\n";

int serv_fd = -1;
void init_server(int portno){ //Инициализация сервера с помощью http-протокола
    serv_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family    = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(portno);
    int enable = 1;
    setsockopt(serv_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));
    bind(serv_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(serv_fd, 10);
}
conn_t get_client(void){
    conn_t connection;
    connection.client_fd = accept(serv_fd, 0, 0);
    connection.fclient = fdopen(connection.client_fd, "r+");
    FILE * f = connection.fclient;
    char rdbuf [2048];
    fgets(rdbuf, 2047, f);
    char * writer = connection.query;
    //Запрос клиента не может содержать пробелы (иначе не заработает из-за свойств браузера и http localhost)
    //Поэтому пробелы клиент кодирует комбинацией %20
    //Здесь же сервер эту комбинацию раскодирует в пробел
    for(const char * reader = rdbuf + 5; reader < rdbuf + strlen(rdbuf) - 11; ++reader){
        if(*reader != '%'){
            *writer++ = *reader;
        } else {
            reader += 2;
            *writer++ = ' ';
        }
    }
    *writer = 0;
    printf("%s\n", connection.query);
    return connection;
}

static void not_found(conn_t connection){ //Если что-то не сработало, то возвращаем ошибку 404
    fprintf(connection.fclient, "HTTP/1.1 404 FILE NOT FOUND\r\n\r\n");
    fclose(connection.fclient);
    shutdown(connection.client_fd, SHUT_RDWR);
}

void process (conn_t connection){
    int is_file_requested = (strstr(connection.query, "select") != connection.query);
    //Эту часть кода мне помогли написать интернет и Дмитрий Маслюков
    //В этой части -- проверка, какой файл клиент запршавивает у сервера,
    //для этапа 4 это и НЕ НУЖНО, но понадобится в будущем,
    //когда сделаю интеграцию с множеством клиентов, и сайтом
    if(is_file_requested){
        FILE * f = fopen(connection.query, "r");
        if(!f){
            not_found(connection);
            return;
        }
        size_t filesize;
        fseek(f, 0, SEEK_END);
        filesize = ftell(f);
        rewind(f);
        char wrbuf [10000];
        unsigned long int bytes_written = 0;
        char * filetype = strstr(connection.query, ".") + 1;
        if(filetype == (char*)1){
            not_found(connection);
        }
        
        const char * mime_type = "text/html";
        
        if(strcmp(filetype, "css") == 0){
            mime_type = "text/css";
        }
        
        if(strcmp(filetype, "js") == 0){
            mime_type = "application/js";
        }
        fprintf(connection.fclient, "HTTP/1.1 200 OK\r\nContent-length: %lu\r\nContent-Type: %s\r\nConnection: close\r\n\r\n", filesize, mime_type);
        
        while(bytes_written < filesize){
            size_t chunk_read = fread(wrbuf, 1, 10000, f);
            fprintf(connection.fclient, "%s", wrbuf);
            bytes_written += chunk_read;
        }
        fclose(connection.fclient);
        shutdown(connection.client_fd, SHUT_RDWR);
    } else {
        printf("%s", connection.query); //На всякий случай вывожу командную строку
        base::index i = b.selectall(connection.query);  //Собственно заданная командной строкой выборка
        b.printall(connection.fclient, i); //Печатаем результат в передаваемый клиенту файл (в сокете)
        fclose(connection.fclient);     //Закрытие клиента
        shutdown(connection.client_fd, SHUT_RDWR);
        //b.printall();
       // b.renewindex(93377); //Не забываем обновить индексы
    }
}
