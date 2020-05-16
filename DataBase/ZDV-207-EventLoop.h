//


#ifndef EventLoop_h
#define EventLoop_h

#include <queue>
#include <mutex>
#include <string>
#include <map>
#include <thread>
#include <time.h>


template<typename T>
class Handler{  //Обработчик
public:
    virtual void call(T arg){}
};


template<typename T, typename F>
class Hdl: public Handler<T>{ //наследуется из Обработчика и хранит непосредственно информацию о функции
    

public:
    F& processor;
    
    Hdl(F & p):processor(p){};
    
    void call (T Arg) override{
        processor(Arg);
    }
};



template<typename T, typename F>
Handler<T> * createHandler(F && p){ //создаёт конкретный обработчик с конкретной функцией
    return new Hdl<T, F>(p);
}




template<typename DataT>
class EventLoop{
public:
    struct eventedData{
        DataT data; //данные события
        std::string event; //описание события
    };
private:
    std::queue<eventedData> data; //очередь из событий, которые и будем обрабатывать
    std::mutex mu_w;
    std::mutex mu_r;
    std::map<std::string, Handler<DataT>*> handlers; //сопоставляет категории (описанию) обработчик
    int numworkers; //количество потоков в обработке событий
    
    struct Worker{
        EventLoop<DataT> & el;
        Worker(EventLoop<DataT> & e):el(e){ //Ждёт события в бесконечном цикле из очереди и обрабатывает
            std::thread([&](){
                while(true){
                    eventedData ev = el.getNext();
                    auto h = el[ev.event];
                    if(h != nullptr){
                        h->call(ev.data); //тут обработка и происходит
                    }
                }
            }).detach();
        }
        
    };
    
    
public:
    
    
    Handler<DataT> * operator[](std::string s){
        if(handlers.find(s) == handlers.end()){
            return nullptr;
        }
        return handlers[s];
    }
    
    void addHandler(Handler<DataT> * h, std::string e){
        handlers[e] = h;
    }
    
    EventLoop(int num){
        numworkers = num;
    }
    
    void start(){ //запускает Worker
        for(int i = 0; i < numworkers; i++){
            new Worker(*this);
        }
    }
    
    void addEvent( eventedData _data ){ //добавляет событие в очередь
        mu_w.lock();
        data.push(_data);
        mu_w.unlock();
    }
    eventedData getNext(){ //когда событие будет, тогда следующий и отдаст
        while(true){
            mu_w.lock();
            if(data.size() == 0){
                mu_w.unlock();
            } else {
                eventedData ev = data.front();
                data.pop();
                mu_w.unlock();
                return ev;
            }
            usleep(500); //если очередь пустая, то ждём
        }
        
        
    }
};


#endif /* EventLoop_h */
