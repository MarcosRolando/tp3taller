#include "client_ClientProtocol.h"
#include "common_TPException.h"
#include <arpa/inet.h>
#include "common_GameProtocolConstants.h"
#include <string>
#include <utility>
#include <vector>

#define HELP_COMMAND "AYUDA"
#define SURRENDER_COMMAND "RENDIRSE"
#define INVALID_COMMAND_MESSAGE "Error: comando inválido. Escriba AYUDA para" \
                                                                " obtener ayuda"

const unsigned int maxNumber = 65535; /*Maximo numero sin signo que */
                                     /*representable en 2 bytes*/

std::vector<char> ClientProtocol::_helpCommand(unsigned int& bufferLength) {
    bufferLength = 1;
    std::vector<char> buffer(bufferLength);
    buffer[0] = HELP_CHAR;
    return buffer;
}

std::vector<char> ClientProtocol::_surrenderCommand(
                                                    unsigned int& bufferLength) {
    bufferLength = 1;
    std::vector<char> buffer(bufferLength);
    buffer[0] = SURRENDER_CHAR;
    return buffer;
}

std::vector<char> ClientProtocol::_numberCommand(std::string&& command,
                                                    unsigned int& bufferLength) {
    bufferLength = 3;
    std::vector<char> buffer(bufferLength);
    buffer[0] = NUMBER_CHAR;
    unsigned int conversionNumber = std::stoi(command);
    if (conversionNumber > maxNumber)
        throw TPException(INVALID_COMMAND_MESSAGE);
    uint16_t number = conversionNumber;
    number = htons(number);
    for (int i = 0; i < 2; ++i) {
        buffer[i + 1] = *(reinterpret_cast<char*>(&number) + i);
    }
    return buffer;
}

std::vector<char> ClientProtocol::translateCommand(std::string&& command,
                                                    unsigned int& bufferLength) {
    if (command == HELP_COMMAND) {
        return _helpCommand(bufferLength);
    } else if (command == SURRENDER_COMMAND) {
        return _surrenderCommand(bufferLength);
    } else {
        try {
            return _numberCommand(std::move(command), bufferLength);
        } catch(std::exception& e) { /*Por si stoi tira exception*/
            throw TPException(INVALID_COMMAND_MESSAGE);
        }
    }
}

bool ClientProtocol::finishedReceiving() const {
    return readResponse;
}

void ClientProtocol::processResponse(std::vector<char>& response) {
    if (!readLength) {
        responseLength = *reinterpret_cast<uint32_t*>(response.data());
        responseLength = ntohl(responseLength);
        ++responseLength; /*Reservo espacio para el \0*/
        readLength = true;
    } else {
        response[responseLength-1] = '\0';
        std::string strResponse = response.data();
        if (strResponse == LOST_MESSAGE || strResponse == WON_MESSAGE)
            finished = true;
        readLength = false;
        readResponse = true;
    }
}

std::vector<char> ClientProtocol::responseBuffer(
                                                unsigned int& bufferLength) {
    if (!readLength) {
        readResponse = false;
        bufferLength = 4;
        std::vector<char> buffer(bufferLength);
        return buffer;
    }  else {
        bufferLength = responseLength - 1; /*No hay \0 en el mensaje a leer*/
        std::vector<char> buffer(responseLength);
        return buffer;
    }
}

bool ClientProtocol::hasFinished() const {
    return finished;
}

