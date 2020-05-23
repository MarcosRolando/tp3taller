#include <netdb.h>
#include "Client.h"
#include <cstring>
#include "User.h"
#include "TPException.h"
#include "OSException.h"
#include <string>

struct addrinfo* Client::_getAddresses() {
    struct addrinfo hints{}, *result;
    int s; /*Para verificar errores*/
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;
    s = getaddrinfo(host.c_str(), port.c_str(), &hints, &result);
    if (s != 0) throw OSException("Error in getaddrinfo: %s", gai_strerror(s));
    return result;
}

void Client::_send() {
    std::string command = User::getInput();
    unsigned int bufferLength;
    std::unique_ptr<char[]> buffer = ClientProtocol::translateCommand(
                                            std::move(command), bufferLength);
    socket.send(buffer.get(), bufferLength);
}

void Client::_receive() {
    unsigned int bufferLength;
    std::unique_ptr<char[]> response;
    do {
        response.reset();
        response = protocol.responseBuffer(bufferLength);
        socket.receive(response.get(), bufferLength);
        protocol.processResponse(response);
    } while (!protocol.finishedReceiving());
    User::showMessage(response.get());
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
