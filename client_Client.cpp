#include <netdb.h>
#include "client_Client.h"
#include <cstring>
#include "client_User.h"
#include "common_TPException.h"
#include "common_OSException.h"
#include <string>
#include <vector>
#include <utility>

#define GETADDRINFO_ERROR_MSG "Error in getaddrinfo: %s"

struct addrinfo* Client::_getAddresses() {
    struct addrinfo hints{}, *result;
    int s; /*Para verificar errores*/
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;
    s = getaddrinfo(host.c_str(), port.c_str(), &hints, &result);
    if (s != 0) throw OSException(GETADDRINFO_ERROR_MSG, gai_strerror(s));
    return result;
}

void Client::_send() {
    std::string command = User::getInput();
    unsigned int bufferLength;
    std::vector<char> buffer = ClientProtocol::translateCommand(
                                            std::move(command), bufferLength);
    socket.send(buffer.data(), bufferLength);
}

void Client::_receive() {
    unsigned int bufferLength;
    std::vector<char> response;
    do {
        response = protocol.responseBuffer(bufferLength);
        socket.receive(response.data(), bufferLength);
        protocol.processResponse(response);
    } while (!protocol.finishedReceiving());
    User::showMessage(response.data());
}

void Client::_processConnection() {
    while (!finished) {
        try {
            _send();
            _receive();
        } catch(TPException& e) {
            User::showMessage(e.what());
        }
        finished = protocol.hasFinished();
    }
}

void Client::connect() {
    struct addrinfo* addresses = _getAddresses();
    try {
        socket.connect(addresses);
    } catch(OSException& e) {
        freeaddrinfo(addresses);
        throw e;
    }
    freeaddrinfo(addresses);
    _processConnection();
}
