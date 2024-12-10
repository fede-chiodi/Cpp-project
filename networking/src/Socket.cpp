#include "../include/Socket.hpp"

Socket::Socket() {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) {
        perror("Errore nella creazione della socket");
        exit(EXIT_FAILURE);
    }
}

Socket::~Socket() {
    close(sockfd);
}

void Socket::bind(int port) {
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if(::bind(sockfd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("errore nel bind");
        exit(EXIT_FAILURE);
    }
}

void Socket::listen(int backlog) {
    if(::listen(sockfd, backlog) < 0) {
        perror("errore nella listen");
        exit(EXIT_FAILURE);
    }
}

void Socket::closeSocket() {
    close(sockfd);
}

void Socket::sendData(int clientSocket, const std::string& message) {
    send(clientSocket, message.c_str(), message.size(), 0);
}

std::string Socket::receiveData(int clientSocket, int bufferSize) {
    char buffer[bufferSize];
    memset(buffer, 0, bufferSize);
    int bytesReceived = recv(clientSocket, buffer, bufferSize, 0);
    if(bytesReceived < 0) {
        perror("errore nel ricevere i dati");
        return "";
    }

    return std::string(buffer, bytesReceived);
}