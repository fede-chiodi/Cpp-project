#include "./include/ServerSocket.hpp"
#include <iostream>
#include <csignal>

bool running = true;

void handle_signal(int signal) {
    if (signal == SIGINT) {
        std::cout << "Server arrestato in modo pulito...\n";
        running = false;
    }
}

int main() {

    std::signal(SIGINT, handle_signal);

    ServerSocket server(8080, 4);
    std::cout << "Server in ascolto sulla porta 8080.... \n";

    while(running) {
        int clientSocket = server.acceptConnection();
        std::cout << "Nuova connessione accettata!\n";

        server.getThreadPool().enqueue([&server, clientSocket]() {
            std::cout << "Inizio gestione del client con socket: " << clientSocket << std::endl;
            server.handleClient(clientSocket);
            std::cout << "Client con socket " << clientSocket << " gestito correttamente." << std::endl;
        });
    }

    std::cout << "Attendere che i thread terminino..." << std::endl;
    server.getThreadPool().waitForCompletion();
    std::cout << "Chiusura socket server..." << std::endl;
    server.closeSocket();
    std::cout << "Server fermato.\n";

return 0;
}