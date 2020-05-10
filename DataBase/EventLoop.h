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
class Handler{
public:
    virtual void call(T arg){}
};


template<typename T, typename F>
class Hdl: public Handler<T>{
    

public:
    F& processor;
    
    Hdl(F & p):processor(p){};
    
    void call (T Arg) override{
        processor(Arg);
    }
};



template<typename T, typename F>
Handler<T> * createHandler(F && p){
    return new Hdl<T, F>(p);
}




template<typename DataT>
class EventLoop{
public:
    struct eventedData{
        DataT data;
        std::string event;
    };
private:
    std::queue<eventedData> data;
    std::mutex mu_w;
    std::mutex mu_r;
    std::map<std::string, Handler<DataT>*> handlers;
    int numworkers;
    
    struct Worker{
        EventLoop<DataT> & el;
        Worker(EventLoop<DataT> & e):el(e){
            std::thread([&](){
                while(true){
                    eventedData ev = el.getNext();
                    auto h = el[ev.event];
                    if(h != nullptr){
                        h->call(ev.data);
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
    
    void start(){
        for(int i = 0; i < numworkers; i++){
            new Worker(*this);
        }
    }
    
    void addEvent( eventedData _data ){
        mu_w.lock();
        data.push(_data);
        mu_w.unlock();
    }
    eventedData getNext(){
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
            usleep(500);
        }
        
        
    }
};


#endif /* EventLoop_h */
