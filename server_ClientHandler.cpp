#include "server_ClientHandler.h"
#include "common_OSException.h"
#include <memory>

void ClientHandler::run() {
    while (!finished) {
        try {
            std::unique_ptr<char[]> message;
            unsigned int bufferLength;
            _receive(message, bufferLength);
            _send(message, bufferLength);
        } catch(OSException& e) {
            finished = true; /*Hubo algun error con el cliente*/
                            /*corto la conexion*/
        }
        if (!finished) finished = protocol.hasFinished();
    }
}

void ClientHandler::_receive(std::unique_ptr<char[]>& message,
                                                unsigned int& bufferLength) {
    do {
        message.reset();
        message = protocol.commandBuffer(bufferLength);
        socket.receive(message.get(), bufferLength);
        protocol.processCommand(message.get());
    } while (!protocol.finishedReceiving());
}

void ClientHandler::_send(std::unique_ptr<char[]>& message,
                                                unsigned int& bufferLength) {
    message = protocol.getResponse(bufferLength);
    socket.send(message.get(), bufferLength);
}

bool ClientHandler::hasFinished() {
    return finished;
}


