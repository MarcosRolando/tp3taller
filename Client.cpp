//
// Created by marcos on 21/5/20.
//

#include <netdb.h>
#include "Client.h"
#include <cstring>

struct addrinfo* Client::_getAddresses() {
    struct addrinfo hints, *result;
    int s; //flag por si hubo un error
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;       /* IPv4 (or AF_INET6 for IPv6)     */
    hints.ai_socktype = SOCK_STREAM; /* TCP  (or SOCK_DGRAM for UDP)    */
    hints.ai_flags = 0;              /* None (or AI_PASSIVE for server) */
    s = getaddrinfo(host.c_str(), port.c_str(), &hints, &result);
    if (s != 0) throw std::exception();
    return result;
}

void Client::_processConnection() {

}

void Client::connect() {
    struct addrinfo* addresses = _getAddresses(this);
    socket.connect(addresses);
    freeaddrinfo(addresses);
    _processConnection();
}
