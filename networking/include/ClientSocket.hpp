#pragma once
#include "./Socket.hpp"

class ClientSocket : public Socket {
    public:
        void connectToServer(const std::string& serverAddress, int port);
};  