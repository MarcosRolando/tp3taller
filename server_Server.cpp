#include <sys/socket.h>
#include <netdb.h>
#include <cstring>
#include <algorithm>
#include "server_Server.h"
#include "server_ClientHandler.h"
#include "server_ServerMonitor.h"
#include "common_OSException.h"

const int MAX_LISTENERS = 10;

struct addrinfo* Server::_getAddresses() {
    struct addrinfo hints{}, *result;
    int s; /*variable para verificar si hubo errores*/
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_protocol = 0;
    s = getaddrinfo(nullptr, port.c_str(), &hints, &result);
    if (s != 0) throw OSException("Error in getaddrinfo: %s", gai_strerror(s));
    return result;
}

/*Funcion que le paso a remove_if para que verifique si termino el cliente*/
bool clientHasFinished(std::unique_ptr<ClientHandler>& client) {
    if (client->hasFinished()) {
        client->join();
        return true;
    }
    return false;
}

void Server::_acceptConnections() {
    unsigned int secretNumber;
    while (!finished) {
        try {
            Socket peer = socket.accept();
            secretNumber = file.getNextNumber();
            clients.emplace_back(new ClientHandler(std::move(peer),
                                                                secretNumber));
            clients.back()->start();
            clients.erase(std::remove_if(clients.begin(),
                    clients.end(), clientHasFinished), clients.end());
        } catch(OSException& e) {
            if (!finished) throw e; /*Hubo un error externo*/
        }
    }
}

void Server::_processConnections() {
    ServerMonitor monitor(*this);
    monitor.start();
    _acceptConnections();
    for (auto & client : clients) {
        client->join();
    }
    monitor.join();
}

void Server::forceFinish() {
    finished = true;
    socket.close();
}

void Server::connect() {
    struct addrinfo* addresses = _getAddresses();
    try {
        socket.bind(addresses);
    } catch(OSException& e) {
        freeaddrinfo(addresses);
        throw e;
    }
    freeaddrinfo(addresses);
    socket.maxListen(MAX_LISTENERS);
    _processConnections();
}
