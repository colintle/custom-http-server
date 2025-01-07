#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <iostream>

class ThreadPool
{
    private:
        vector<thread> threads_;
        queue<function<void()> > tasks_;
        mutex queue_mutex_;
        condition_variable cv_;
        bool stop_ = false;
        
    public:
        ThreadPool(int num_threads);
        void add_task(void (*task)(void*), void* args);
        void enqueue();
        ~ThreadPool();
};

#endif