#include "../include/Client.hpp"

Client::Client(const std::string& server_ip, int server_port) {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) {
        std::cerr << "Error creating socket." << std::endl;
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    server_addr.sin_addr.s_addr = inet_addr(server_ip.c_str());
}

Client::~Client() {
    close(sockfd);
}

void Client::read_message() {
    char buffer[1024];
    while(true) {
        size_t buff_size = read(sockfd, buffer, sizeof(buffer));
        if(buff_size <= 0)
            break;
        
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "\nMessage from server: " << std::string(buffer, buff_size) << std::endl;
        std::cout << "Enter your message: " << std::flush;
    }
}

void Client::send_message() {
    std::string message;
    while(true) {
        std::cout << "Enter your message: ";
        std::getline(std::cin, message);
        if(message.empty()) continue;
        std::cout << "Sending message: " << message << std::endl;
        ssize_t bytes_sent = write(sockfd, message.c_str(), message.length());
        if (bytes_sent < 0) {
            std::cerr << "Error writing message to server." << std::endl;
        }
    }
}

void Client::start() {
    if(connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Error connecting to server." << std::endl;
        exit(1);
    }

    std::thread read_thread(&Client::read_message, this);
    std::thread send_thread(&Client::send_message, this);

    read_thread.join();
    send_thread.join();
}