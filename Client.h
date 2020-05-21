//
// Created by marcos on 21/5/20.
//

#ifndef TP3TALLER_CLIENT_H
#define TP3TALLER_CLIENT_H

#include "Socket.h"
#include "ClientProtocol.h"
#include <string>

class Client {
private:
    std::string host, port;
    Socket socket;
public:
    Client(std::string&& host, std::string&& port) : host(host), port(port) {};
    void connect();
private:
    struct addrinfo* _getAddresses();
    void _processConnection();
};


#endif //TP3TALLER_CLIENT_H
