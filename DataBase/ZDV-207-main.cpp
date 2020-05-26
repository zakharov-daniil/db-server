//
//  main.cpp
//  DataBase
//  Zakharov Daniil Vadimovich 207 gr.
//
//  Created by Daniil Zakharov on 24.02.2020.
//  Copyright © 2020 Daniil Zakharov. All rights reserved.
//

#include <iostream>
#include <string>
#include "ZDV-207-generator.h"
#include "ZDV-207-classbase.h"
#include "ZDV-207-FullBase.h"
#include "ZDV-207-server.hpp"
#include "ZDV-207-EventLoop.h"
#include "ZDV-207-htmlElement.h"
int main() {
    
    //ЗАГРУЗКА
    int size = 93377;
    FILE *fout;
    fout = fopen("output.txt", "r");
    //base b;
    b.makebase(fout, size);
    fclose(fout);
    
    EventLoop<conn_t> loop(4); //будем делать 4 одновременных потока
    
    loop.addHandler(createHandler<conn_t>([](conn_t c){ //подключаем обработчик на запрос к БД
        process(c);
    }), "connection"); //собственно подсключения
    
    loop.start();
    init_server(3227); //Инициализируем сервер
    
    
    while (1) {
        conn_t connection = get_client(); //Получаем клиента
        loop.addEvent(EventLoop<conn_t>::eventedData{
            connection,
            "connection"
        });
    }
    
    
    
    
    
    /*
    //ЭТАП 3
    //МНОЖЕСТВЕННЫЙ ВЫБОР -- ПО 3, ПО 4 ПАРАМЕТРАМ (можно и меньше)
     char com[200] = "select date= 2002-2003 student= ЗАПЛАТОВ subject= Анализ  "; // Командная строка
    base::index idx = b.selectall(com); // Собственно выборка
    b.printall(stdout,idx); // Распечатка всего результата -- будет всего 3 записи
    */
   // b.renewindex(93377); // Восстановление исходных индексов (иначе программа будет думать, что происходит дополнительная выборка)
    /*
    char com1[200] = "select date= 2002-2003 student= ТИНЬКОВ subject= Топология lector= Адам РАДИК"; // Командная строка
    b.selectall(com1); // Собственно выборка
    b.printall(); // Распечатка всего результата -- будет всего одна запись
    b.renewindex(93377); // Снова восстановление индексов
    */
    
    /* //ВЫБОР ТОЛЬКО ПО ДАТЕ -- к ЭТАПУ 2
    b.selectdate("2002-2003");
    b.getindexrecord(b.getsize()-1).printrecord();
    // b.printall(); // Можно распечатать всё, но это будет много
    b.renewindex(93377);
    */
    
    /* //ВЫБОР ТОЛЬКО ПО ПРЕДМЕТУ
    b.selectsubject("Матстат");
    b.getindexrecord(b.getsize()-1).printrecord();
    // b.printall(); // Можно распечатать всё, но это будет много
    b.renewindex(93377);
    */
    
    /* //ВЫБОР ТОЛЬКО ПО ЛЕКТОРУ
    b.selectlector("Афиноген", "БАБАНОВ");
    b.getindexrecord(b.getsize()-1).printrecord();
    // b.printall() // Можно распечатать всё, но это будет много
    b.renewindex(93377);
     */
    
    /* //ВЫБОР ТОЛЬКО ПО СТУДЕНТУ
    b.selectstudent("ТИНЬКОВ");
    b.getindexrecord(b.getsize()-1).printrecord();
    // b.printall(); // Можно распечатать всё, но это будет много
    b.renewindex(93377);
     */
    
    //ДОБАВЛЕНИЕ В БД
    
    /*char com2[400] = "add Парамон   ЛАЗАРЕНКО   Предмет: ТЧ   Дата: 2004-2005   Студенты: ЗАСЕЦКИЙ ЗАСТОЛБСКИЙ ЗАСУРСКИЙ \n";
    //b.addrecord(com);
    b.selectall(com2);
    b.getindexrecord(b.getsize()-1).printrecord(); //Проверка, что всё сработало -- печатаем последний элемент бд
    
    //И СРАЗУ УДАЛЕНИЕ ТОГО ЖЕ
    char com3[400] = "delete Парамон   ЛАЗАРЕНКО   Предмет: ТЧ   Дата: 2004-2005   Студенты: ЗАСЕЦКИЙ ЗАСТОЛБСКИЙ ЗАСУРСКИЙ \n";
    //b.offrecord(com1);
    b.selectall(com3);
    b.getindexrecord(b.getsize()-1).printrecord(); //Проверка, что всё сработало -- теперь конец такой же как и был до добавления
    */
    
    /* //ГЕНЕРАТОР -- ЭТАП 1
      FILE *Surnams, *Names, *Lectures, *Dates, *fout;
    int num1=0, num2=0, num3=0, num4=0;
    int size = 99999;
    
    Surnams = fopen("surname.txt", "r");
    Names = fopen("name.txt", "r");
    Lectures = fopen("lecture.txt", "r");
    Dates = fopen("date.txt", "r");
    if (!Surnams || !Names || !Lectures || !Dates) {
        printf("File opening error\n");
        return -1;
    }
    fout = fopen("output.txt", "w");
    
    char **surn, **name, **lect, **date, **rSurnam, **rNam, **rLect, **rDate;
    
    surn = wordcpy(Surnams, num1);
    fclose(Surnams);
    rSurnam = wordrand(surn, num1, size);
    
    name = wordcpy(Names, num2);
    fclose(Names);
    rNam = wordrand(name, num2, size);
    
    lect = wordcpy(Lectures, num3);
    fclose(Lectures);
    rLect = wordrand(lect, num3, size);
    
    date = wordcpy(Dates, num4);
    fclose(Dates);
    rDate = wordrand(date, num4, size);
    
    printString(fout, rNam, rSurnam, rLect, rDate, size);
    fclose(fout);
    
    free(surn);
    free(rSurnam);
    free(name);
    free(rNam);
    free(lect);
    free(rLect);
    printf("%d\n",size);*/
    
    
    return 0;
}
