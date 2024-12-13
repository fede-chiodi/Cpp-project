#pragma once

#include<iostream>
#include<string>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>

class Client {
    private:
        int sockfd;
        struct sockaddr_in server_addr;
        std::mutex mtx;

        void read_message();
        void send_message();

    public:

        Client(const std::string& server_ip, int server_port);
        ~Client();

        void start();
};