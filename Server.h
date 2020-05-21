//
// Created by marcos on 25/4/20.
//

#ifndef TP1_SERVER_H
#define TP1_SERVER_H

#include "Socket.h"
#include <string>

class Server {
private:
    std::string port;
    Socket socket;
public:
    explicit Server(std::string&& port) : port(std::move(port)) {};
private:
    void _connect();
    struct addrinfo* _getAddresses();
};

#endif //TP1_SERVER_H
