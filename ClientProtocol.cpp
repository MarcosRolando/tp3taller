#include "ClientProtocol.h"
#include "TPException.h"
#include <arpa/inet.h>
#include "GameProtocolConstants.h"

#define HELP_COMMAND "AYUDA"
#define SURRENDER_COMMAND "RENDIRSE"
#define INVALID_COMMAND_MESSAGE "Error: comando inválido. Escriba AYUDA para" \
                                                                " obtener ayuda"

const unsigned int maxNumber = 65535; /*Maximo numero sin signo que representable
                                     * en 2 bytes*/

std::unique_ptr<char[]> ClientProtocol::_helpCommand(unsigned int& bufferSize) {
    bufferSize = 1;
    std::unique_ptr<char[]> buffer(new char[bufferSize]());
    buffer[0] = HELP_CHAR;
    return buffer;
}

std::unique_ptr<char[]> ClientProtocol::_surrenderCommand(unsigned int& bufferSize) {
    bufferSize = 1;
    std::unique_ptr<char[]> buffer(new char[bufferSize]());
    buffer[0] = SURRENDER_CHAR;
    return buffer;
}

std::unique_ptr<char[]> ClientProtocol::_numberCommand(std::string&& command,
                                                    unsigned int& bufferSize) {
    bufferSize = 3;
    std::unique_ptr<char[]> buffer(new char[bufferSize]());
    buffer[0] = NUMBER_CHAR;
    unsigned int conversionNumber = std::stoi(command);
    if (conversionNumber > maxNumber) throw TPException(INVALID_COMMAND_MESSAGE);
    uint16_t number = conversionNumber;
    number = htons(number);
    for (int i = 0; i < 2; ++i) {
        buffer[i + 1] = *(reinterpret_cast<char*>(&number) + i);
    }
    return buffer;
}

std::unique_ptr<char []> ClientProtocol::translateCommand(std::string&& command,
                                                    unsigned int& bufferSize) {
    if (command == HELP_COMMAND) {
        return _helpCommand(bufferSize);
    } else if (command == SURRENDER_COMMAND) {
        return _surrenderCommand(bufferSize);
    } else {
        try {
            return _numberCommand(std::move(command), bufferSize);
        } catch (std::invalid_argument& e) { /*Por si recibo texto invalido*/
            throw TPException(INVALID_COMMAND_MESSAGE);
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
        ++responseLength; /*Reservo espacio para el \0*/
        readLength = true;
    } else {
        response[responseLength-1] = '\0';
        std::string strResponse = response.get();
        if (strResponse == LOST_MESSAGE || strResponse == WON_MESSAGE) finished = true;
        readLength = false;
        readResponse = true;
    }
}

std::unique_ptr<char[]> ClientProtocol::responseBuffer(unsigned int& bufferLength) {
    if (!readLength) {
        readResponse = false;
        bufferLength = 4;
        std::unique_ptr<char[]> buffer(new char[bufferLength]());
        return buffer;
    }  else {
        bufferLength = responseLength - 1; /*No hay \0 en el mensaje a leer*/
        std::unique_ptr<char[]> buffer(new char[responseLength]());
        return buffer;
    }
}

bool ClientProtocol::hasFinished() const {
    return finished;
}

