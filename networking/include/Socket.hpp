#pragma once
#include <iostream>
#include <string>
#include <cstring> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <unistd.h> 

class Socket {
    protected:
        int sockfd;
        struct sockaddr_in address;
    public:
        Socket();
        virtual ~Socket();
        void bind(int port);
        void listen(int backlog = 5);
        void closeSocket();
        void sendData(int clientSocket, const std::string& message);
        std::string receiveData(int clientSocket, int bufferSize = 1024);

        int getSocketfd() const {
            return sockfd;
        }
};