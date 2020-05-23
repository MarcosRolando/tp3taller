#include "ClientHandler.h"
#include "OSException.h"

void ClientHandler::run() {
    while (!finished) {
        try {
            unsigned int bufferLength;
            std::unique_ptr<char[]> message;
            do {
                message.reset();
                message = protocol.commandBuffer(bufferLength);
                socket.receive(message.get(), bufferLength);
                protocol.processCommand(message.get());
            } while(!protocol.finishedReceiving());
            message = protocol.getResponse(bufferLength);
            socket.send(message.get(), bufferLength);
        } catch (OSException& e){}
        finished = protocol.hasFinished();
    }
}

bool ClientHandler::hasFinished() {
    return finished;
}


