#include "./include/Client.hpp"

int main() {
    std::string server_ip = "127.0.0.1";
    int server_port = 8080;

    Client client(server_ip, server_port);
    client.start();

return 0;
}