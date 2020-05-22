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
    ClientProtocol protocol;
    bool finished;
public:
    Client(std::string&& host, std::string&& port) : host(host), port(port), finished(false) {};
    void connect();
private:
    void _send();
    void _receive();
    struct addrinfo* _getAddresses();
    void _processConnection();
};


#endif //TP3TALLER_CLIENT_H
