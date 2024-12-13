#pragma once

#include <vector>
#include <queue>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <atomic>

class ThreadPool {
    private:
        std::vector<std::thread> threads;
        std::queue<std::function<void()>> tasks;
        std::mutex queue_mtx;
        std::condition_variable cv;
        std::atomic<bool> stop;

        void worker_thread();
    
    public:
        ThreadPool(size_t threads_number);
        ~ThreadPool();
        void enqueue_task(std::function<void()> task);
};