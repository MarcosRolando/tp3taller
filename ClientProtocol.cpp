//
// Created by marcos on 21/5/20.
//

#include "ClientProtocol.h"
#include "TPException.h"
#include <arpa/inet.h>

std::unique_ptr<char[]> ClientProtocol::_helpCommand(unsigned int& bufferSize) {
    bufferSize = 1;
    std::unique_ptr<char[]> buffer(new char[bufferSize]());
    buffer[0] = 'h';
    return buffer;
}

std::unique_ptr<char[]> ClientProtocol::_surrenderCommand(unsigned int& bufferSize) {
    bufferSize = 1;
    std::unique_ptr<char[]> buffer(new char[bufferSize]());
    buffer[0] = 's';
    return buffer;
}

std::unique_ptr<char[]> ClientProtocol::_numberCommand(std::string&& command,
                                                    unsigned int& bufferSize) {
    bufferSize = 3;
    std::unique_ptr<char[]> buffer(new char[bufferSize]());
    buffer[0] = 'n';
    uint16_t number = std::stoi(command);
    number = htons(number);
    for (int i = 0; i < 2; ++i) {
        buffer[i + 1] = *(reinterpret_cast<char*>(&number) + i);
    }
    return buffer;
}

std::unique_ptr<char []> ClientProtocol::translateCommand(std::string&& command,
                                                    unsigned int& bufferSize) {
    if (command == "AYUDA") {
        return _helpCommand(bufferSize);
    } else if (command == "RENDIRSE") {
        return _surrenderCommand(bufferSize);
    } else {
        try {
            return _numberCommand(std::move(command), bufferSize);
        } catch (std::invalid_argument& e) {
            throw TPException("Error: comando inválido. Escriba AYUDA para obtener ayuda");
        }
    }
}

bool ClientProtocol::finishedReceiving() const {
    return readResponse;
}

void ClientProtocol::processResponse(std::unique_ptr<char[]>& response) {
    if (!readLength) {
        responseLength = *reinterpret_cast<uint32_t*>(response.get());
        responseLength = ntohl(responseLength);
        responseLength++; /*cuento el \0*/
        readLength = true;
    } else {
        response[responseLength-1] = '\0';
        std::string strResponse = response.get();
        if (strResponse == "Perdiste" || strResponse == "Ganaste") finished = true;
        readLength = false;
        readResponse = true;
    }
}

std::unique_ptr<char[]> ClientProtocol::responseBuffer(unsigned int& bufferLength) {
    if (!readLength) { /*esto es muy rancio, cambiarlo*/
        readResponse = false;
        bufferLength = 4;
        std::unique_ptr<char[]> buffer(new char[bufferLength]());
        return buffer;
    }  else {
        bufferLength = responseLength - 1; /*no hay \0 en el mensaje a leer*/
        std::unique_ptr<char[]> buffer(new char[responseLength]());
        return buffer;
    }
}

bool ClientProtocol::hasFinished() const {
    return finished;
}

