#include <iostream>
#include "../include/ServerSocket.hpp"

ServerSocket::ServerSocket(int port, size_t threadsCounter) : threadpool(threadsCounter) {
    bind(port);
    listen(5);   
}

int ServerSocket::acceptConnection() {
    int addrlen = sizeof(address);
    int newSocket = accept(getSocketfd(), (struct sockaddr*)&address, (socklen_t*)&addrlen);
    if (newSocket < 0) {
        perror("Errore nell'accettazione della connessione");
        exit(EXIT_FAILURE);
    }
    return newSocket;
}

void ServerSocket::handleClient(int clientSocket) {
    std::cout << "Gestione client su thread separato, socket: " << clientSocket << std::endl;
    std::string message = receiveData(clientSocket);
    std::cout << "Messaggio ricevuto: " << message << std::endl;
    sendData(clientSocket, "Messagguio ricevuto dal server");
    close(clientSocket);
    std::cout << "connessione chiusa con il client. \n";
}