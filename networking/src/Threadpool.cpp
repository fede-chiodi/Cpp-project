#include "../include/ThreadPool.hpp"

ThreadPool::ThreadPool(size_t threadsCounter) : stop(false) {
    for(size_t i = 0; i < threadsCounter; i++) {
        threads.emplace_back([this] {
            while(true) {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(queueMtx);
                    condition.wait(lock, [this] { return stop || !tasks.empty(); });
                    if(stop && tasks.empty()) 
                        return;
                    else {
                        task = std::move(tasks.front());
                        tasks.pop();
                    }
                }
                task();
            }
        });
    }
}

void ThreadPool::enqueue(std::function<void()> task) {
    {
        std::lock_guard<std::mutex> lock(queueMtx);
        tasks.push(task);
    }
    condition.notify_one();
}

ThreadPool::~ThreadPool() {
    stop = true;
    condition.notify_all();
    for (std::thread &thread : threads) {
        if (thread.joinable()) thread.join();
    }
}