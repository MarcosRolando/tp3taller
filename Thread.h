//
// Created by marcos on 12/5/20.
//

#ifndef TP2TALLER_THREAD_H
#define TP2TALLER_THREAD_H

#include <thread>

class Thread {
private:
    std::thread thread;
public:
    void start();
    void join();
    virtual void run() = 0;
};


#endif //TP2TALLER_THREAD_H
