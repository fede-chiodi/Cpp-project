#include "../include/ThreadPool.hpp"

ThreadPool::ThreadPool(size_t threads_number) : stop(false) {
    for(size_t i = 0; i < threads_number; i++)
        threads.push_back(std::thread(&ThreadPool::worker_thread, this));
}

ThreadPool::~ThreadPool() {
    stop = true;
    cv.notify_all();

    for(std::thread& t : threads) {
        if(t.joinable())
            t.join();
    }
}

void ThreadPool::enqueue_task(std::function<void()> task) {
    {
        std::lock_guard<std::mutex> lock(queue_mtx);
        tasks.push(task);
    }
    cv.notify_all();
}

void ThreadPool::worker_thread() {
    while(!stop) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(queue_mtx);
            cv.wait(lock, [this]{ return !tasks.empty() || stop; });
            if(stop && tasks.empty()) return;

            task = std::move(tasks.front());
            tasks.pop();
        }
        task();
    }
}