#pragma once
#include "./Socket.hpp"
#include "./ThreadPool.hpp"

class ServerSocket : public Socket {
    private:
        ThreadPool threadpool;
    public:
        ServerSocket(int port, size_t threadsCount);
        int acceptConnection();
        void handleClient(int clientSocket);

        ThreadPool& getThreadPool() {
            return threadpool;
        }
};