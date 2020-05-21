//
// Created by marcos on 21/5/20.
//

#include <netdb.h>
#include "Client.h"
#include <cstring>
#include "User.h"
#include "TPException.h"
#include <iostream>

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
    bool finished = false;
    std::string command;
    unsigned int bufferLength;
    while (!finished) {
        command = User::getInput();
        try {
            std::unique_ptr<char[]> buffer = ClientProtocol::translateCommand(
                                        std::move(command), bufferLength);
            socket.send(buffer.get(), bufferLength);
            /*aca tengo que recibir el mensaje del servidor*/
        } catch (TPException& e) {
            std::cout << e.what() << std::endl; /*esto es medio sidoso, ver bien donde lo manejo*/
        }
    }
}

void Client::connect() {
    struct addrinfo* addresses = _getAddresses();
    socket.connect(addresses);
    freeaddrinfo(addresses);
    _processConnection();
}
