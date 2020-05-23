//
// Created by marcos on 20/5/20.
//

#include "ClientHandler.h"
#include "ClosedSocketException.h"

void ClientHandler::run() {
    while (!finished) {
        try {
            unsigned int bufferSize = 1;
            while (bufferSize != 0) {
                std::unique_ptr<char[]> buffer(new char[bufferSize]);
                socket.receive(buffer.get(), bufferSize);
                bufferSize = protocol.processCommand(buffer.get());
            }
            std::unique_ptr<char[]> response = protocol.getResponse(bufferSize);
            socket.send(response.get(), bufferSize);
        } catch (ClosedSocketException& e){}
        if (!finished)  {
            finished = protocol.hasFinished();
        }
    }
}

bool ClientHandler::hasFinished() {
    return finished;
}


