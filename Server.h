//
// Created by marcos on 25/4/20.
//

#ifndef TP1_SERVER_H
#define TP1_SERVER_H

#include "Socket.h"
#include "FileReader.h"
#include <string>
#include <atomic>
#include "ClientHandler.h"

class Server {
private:
    std::atomic<bool> finished;
    std::string port;
    Socket socket;
    FileReader file;
public:
    Server(std::string&& port, std::string&& fileName) : finished(false),
                            port(std::move(port)), file(std::move(fileName)) {};
    void connect();
    void forceFinish();
private:
    struct addrinfo* _getAddresses();
    void _acceptConnections();
};

#endif //TP1_SERVER_H
