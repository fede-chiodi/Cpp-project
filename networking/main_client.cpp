#include "./include/ClientSocket.hpp"
#include <iostream>

int main() {

    ClientSocket client;
    client.connectToServer("127.0.0.1", 8080);

    std::string message = "Hello, I'm the client";
    client.sendData(client.getSocketfd(), message);
    std::cout << "Messaggio inviato al server\n";

    std::string response = client.receiveData(client.getSocketfd());
    std::cout << "Risposta dal server: " << response << std::endl;

    client.closeSocket();

return 0;
}