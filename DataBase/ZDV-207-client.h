//
//  Header.h
//  client
//
//  Created by Daniil Zakharov on 23.04.2020.
//  Copyright © 2020 Daniil Zakharov. All rights reserved.
//

#ifndef Header_h
#define Header_h
#include <sys/socket.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<unistd.h>
#include <netinet/in.h>
class Client{
    
//Под копирку из файла cli_tcp.cpp
//Вплоть до интеграции с http-протоколами
//В будущем, видимо, сделаю ещё один .cpp файл для большей технологической правильности
public:
    static FILE * request(const char * command, const char * hostname, int portno){
            int err;
            int sock;
            struct sockaddr_in server_addr;
            struct hostent    *hostinfo;

            // Получаем информацию о сервере по его DNS имени
            // или точечной нотации IP адреса.
            hostinfo = gethostbyname(hostname);
            if ( hostinfo==NULL ) {
                fprintf (stderr, "Unknown host %s.\n",hostname);
                exit (EXIT_FAILURE);
            }

            // Заполняем адресную структуру для последующего
            // использования при установлении соединения
            server_addr.sin_family = AF_INET;
            server_addr.sin_port = htons(portno);
            server_addr.sin_addr = *(struct in_addr*) hostinfo->h_addr;
        //for (i=0;i<100000;i++) {
            // Создаем TCP сокет.
            sock = socket(AF_INET, SOCK_STREAM, 0);
            if ( sock<0 ) {
                perror ("Client: socket was not created");
                exit (EXIT_FAILURE);
            }

            // Устанавливаем соединение с сервером
            err = connect (sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
            if ( err<0 ) {
                perror ("Client:  connect failure");
                exit (EXIT_FAILURE);
            }
            fprintf (stdout,"Connection is ready\n");
        //конструируем http-строку для отправляемого запроса
        FILE * client = fdopen(sock, "r+");
        fprintf(client, "GET /%s HTTP/1.1\r\nHost: %s\r\nAccept: text/html\r\nConnection: close\r\n\r\n",command, hostname );
        fflush(client);
        return client;
        
    }
};

#endif /* Header_h */
