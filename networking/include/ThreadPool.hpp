#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <thread> 
#include <mutex> 
#include <condition_variable> 
#include <functional> 

class ThreadPool{
    private:
        std::vector<std::thread> threads; 
        std::queue<std::function<void()>> tasks;
        std::mutex queueMtx; 
        std::condition_variable condition; 
        bool stop; 
    public:
        ThreadPool(size_t threadsCount);
        void enqueue(std::function<void()> task);
        void waitForCompletion() {
            for (std::thread &thread : threads) {
                if (thread.joinable()) thread.join();
            }
        }
        ~ThreadPool();
};