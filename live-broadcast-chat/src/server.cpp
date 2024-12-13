#include"../include/Server.hpp"
#include<cstring>

Server::Server(int port, size_t threads_numer) : threadpool(threads_numer) {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) {
        std::cerr << "Error creating socket." << std::endl;
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;
}

Server::~Server() {
    close(sockfd);
    for(size_t client_socket : client_sockets) 
        close(client_socket);
}

void Server::accept_connection() {
    if(bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Error binding socket." << std::endl;
        exit(1);
    }

    listen(sockfd, 3);
    std::cout << "Server is listening for connection...." << std::endl;

    while(true) {
        int client_socket = accept(sockfd, NULL, NULL);
        if(client_socket < 0) {
            std::cerr << "Error accepting connection." << std::endl;
            continue;
        }
        std::cout << "Client connected!" << std::endl;
        client_sockets.push_back(client_socket);
        threadpool.enqueue_task([this, client_socket] {handle_client(client_socket); });
    }
}

void Server::handle_client(int client_socket) {
    char buffer[1024];
    while(true) {
        memset(buffer, 0, sizeof(buffer));
        size_t len = read(client_socket, buffer, sizeof(buffer));
        if(len <= 0) {
            break;
        }

        buffer[len] = '\0';

        if (len == 0) {
            std::cout << "Client disconnected." << std::endl; 
            break; 
        }

        std::string message(buffer, len);
        broadcast_message(message, client_socket);
    }
    close(client_socket);
    client_sockets.erase(std::remove(client_sockets.begin(), client_sockets.end(), client_socket), client_sockets.end());
   
}

void Server::broadcast_message(const std::string& str, int sender_socket) {
    std::cout << "Broadcasting message: " << str << std::endl;
    for(int client : client_sockets) {
        if(client != sender_socket) {
            ssize_t bytes_sent = write(client, str.c_str(), str.length());
            if (bytes_sent < 0) {
                std::cerr << "Error sending message to client." << std::endl;
            }
        }
    }
}


void Server::start() {
    accept_connection();
}