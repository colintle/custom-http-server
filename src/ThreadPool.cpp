#include "ThreadPool.h"

ThreadPool::ThreadPool(int threads) : stop_(false) {
  for (int i = 0; i < threads; ++i) {
    this->threads_.emplace_back([this] {
        for (;;) {
            std::function<void()> task;
            {
                std::unique_lock<std::mutex> lock(this->queue_mutex_);
                this->cv_.wait(lock, [this] 
                { 
                    return this->stop_ || !this->tasks_.empty(); 
                });
                if (this->stop_ && this->tasks_.empty()) {
                    return;
                }
                task = std::move(this->tasks_.front());
                this->tasks_.pop();
            }
        task();
      }
    });
  }
}

void ThreadPool::enqueue(std::function<void()> task) {
    {
        std::unique_lock<std::mutex> lock(this->queue_mutex_);
        this->tasks_.emplace(move(task));
    }
    this->cv_.notify_one();
}

ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(this->queue_mutex_);
        this->stop_ = true;
    }
    this->cv_.notify_all();
    for (std::thread &worker : this->threads_) 
    {
        worker.join();
    }
}