#include "../include/ClientSocket.hpp"
#include <arpa/inet.h>

void ClientSocket::connectToServer(const std::string& serverAddress, int port) {
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    if(inet_pton(AF_INET, serverAddress.c_str(), &address.sin_addr) <= 0) {
        perror("Indirizzo non valido o non supportato");
        exit(EXIT_FAILURE);
    }

    if(connect(sockfd, (struct sockaddr*)&address, sizeof(address)) < 0 ) {
        perror("Connessione fallita");
        exit(EXIT_FAILURE);
    }
}