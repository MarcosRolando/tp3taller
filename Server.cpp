//
// Created by marcos on 20/5/20.
//
#include <sys/socket.h>
#include <netdb.h>
#include <cstring>
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

void Server::connect() {
    struct addrinfo* addresses = _getAddresses();
    socket.bind(addresses);
    freeaddrinfo(addresses); //en este punto ya logre bindear al socket
    socket.maxListen(MAX_LISTENERS);
    Socket peer = socket.accept(); //acepto la conexion
    ClientHandler cHandler(std::move(peer), 123);
    cHandler.run();
}
