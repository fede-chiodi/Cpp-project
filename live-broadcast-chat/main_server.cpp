#include "./include/Server.hpp"

int main() {
    int port = 8080;
    size_t thread_count = 4;

    Server server(port, thread_count);
    server.start();

return 0;
}