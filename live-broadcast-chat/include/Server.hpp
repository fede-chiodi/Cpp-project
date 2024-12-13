#pragma once

#include<iostream>
#include<string>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<unistd.h>
#include<netinet/in.h>
#include"../include/ThreadPool.hpp"

class Server {
    private:
        int sockfd;
        struct sockaddr_in server_addr;

        std::vector<int> client_sockets;
        ThreadPool threadpool;

        void accept_connection();
        void handle_client(int client_socket);
        void broadcast_message(const std::string& str, int sender_socket);

    public:
    Server(int port, size_t threadcount);
    ~Server();
    void start();
};
