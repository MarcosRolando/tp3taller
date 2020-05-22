//
// Created by marcos on 20/5/20.
//
#include <sys/socket.h>
#include <netdb.h>
#include <cstring>
#include <algorithm>
#include "Server.h"
#include "ClientHandler.h"

const int MAX_LISTENERS = 1;

struct addrinfo* Server::_getAddresses() {
    struct addrinfo hints{}, *result;
    int s; //flag por si hubo un error
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_STREAM; /* TCP socket */
    hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
    hints.ai_protocol = 0;          /* Any protocol */
    s = getaddrinfo(nullptr, port.c_str(), &hints, &result);
    if (s != 0) throw std::exception(); //ver bien despues de mostrar el error y catchear esto etc
    return result;
}

bool clientHasFinished(ClientHandler*& client) {
    if (client->hasFinished()) {
        client->join();
        return true;
    }
    return false;
}

void Server::_acceptConnections() {
    std::vector<ClientHandler*> clients;
    unsigned short int secretNumber;
    while (!finished) {
        Socket peer = socket.accept(); //acepto la conexion
        secretNumber = file.getNextNumber();
        clients.push_back(new ClientHandler(std::move(peer), secretNumber));
        clients.back()->run();
        clients.erase(std::remove_if(clients.begin(), clients.end(), clientHasFinished), clients.end());
    }
}

void Server::connect() {
    struct addrinfo* addresses = _getAddresses();
    socket.bind(addresses);
    freeaddrinfo(addresses); //en este punto ya logre bindear al socket
    socket.maxListen(MAX_LISTENERS);
    _acceptConnections();
}
