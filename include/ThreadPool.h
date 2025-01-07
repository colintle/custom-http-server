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
        std::vector<std::thread> threads_;
        std::queue<std::function<void()> > tasks_;
        std::mutex queue_mutex_;
        std::condition_variable cv_;
        bool stop_ = false;
        
    public:
        ThreadPool(int num_threads);
        void enqueue(std::function<void()> task);
        ~ThreadPool();
};

#endif
