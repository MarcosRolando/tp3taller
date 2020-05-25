#include "server_ServerProtocol.h"
#include <arpa/inet.h>
#include <cstring>
#include "common_TPException.h"
#include "common_GameProtocolConstants.h"

#define HELP_MESSAGE "Comandos válidos:\n\tAYUDA: despliega la lista" \
                        " de comandos válidos\n\tRENDIRSE: pierde el juego" \
                        " automáticamente\n\tXXX: Número de 3 cifras a ser " \
                        "enviado al servidor para adivinar el número secreto"


#define INVALID_NUMBER_MESSAGE "Número inválido. Debe ser de 3 cifras no " \
                                                                    "repetidas"

const unsigned int PERFECT_SCORE = 30;

void ServerProtocol::_helpCommand() {
    response = HELP_MESSAGE;
}

void ServerProtocol::_surrenderCommand() {
    game.surrender();
    response = LOST_MESSAGE;
}

void ServerProtocol::_setGuessResult(unsigned int score) {
    unsigned int firstDigit = (score / 10) % 10;
    unsigned int secondDigit = score % 10;
    response.clear();
    if (firstDigit == 0 && secondDigit == 0) {
        response += "3 mal";
    } else if (firstDigit != 0) {
        response += std::to_string(firstDigit) + " bien";
        if (secondDigit != 0) response += ", " + std::to_string(secondDigit) +
                                                                    " regular";
    } else {
        response += std::to_string(secondDigit) + " regular";
    }
}

void ServerProtocol::_numberCommand(const char* clientCommand) {
    uint16_t number = *(reinterpret_cast<const uint16_t *>(clientCommand));
    number = ntohs(number);
    try {
        unsigned int score = game.guess(number);
        if (game.hasFinished()) {
            if (score == PERFECT_SCORE)
                response = WON_MESSAGE;
            else
                response = LOST_MESSAGE;
        } else {
            _setGuessResult(score);
        }
    } catch(TPException& e) {
        if (game.hasFinished())
            response = LOST_MESSAGE;
        else
            response = INVALID_NUMBER_MESSAGE;
    }
}

std::vector<char> ServerProtocol::commandBuffer(
                                                unsigned int& bufferLength) {
    readCommand = false;
    if (!receivingNumber) {
        bufferLength = 1;
        std::vector<char> buffer(bufferLength);
        return buffer;
    } else {
        bufferLength = 2;
        std::vector<char> buffer(bufferLength);
        return buffer;
    }
}


void ServerProtocol::processCommand(const char* clientCommand) {
    if (receivingNumber) {
        _numberCommand(clientCommand);
        receivingNumber = false;
        readCommand = true;
    } else if (*clientCommand == HELP_CHAR) {
        _helpCommand();
        readCommand = true;
    } else if (*clientCommand == SURRENDER_CHAR) {
        _surrenderCommand();
        readCommand = true;
    } else if (*clientCommand == NUMBER_CHAR) {
        receivingNumber = true;
    }
}

std::vector<char> ServerProtocol::getResponse(unsigned int& bufferLength) const{
    uint32_t msgLength = response.length();
    bufferLength = msgLength + 4;
    std::vector<char> responseMsg(bufferLength);
    msgLength = htonl(msgLength);
    for (int i = 0; i < 4; ++i) {
        responseMsg[i] = *(reinterpret_cast<char*>(&msgLength) + i);
    }
    int i = 4;
    for (auto & c : response) {
        responseMsg[i] = c;
        ++i;
    }
    return responseMsg;
}

bool ServerProtocol::hasFinished() const {
    return game.hasFinished();
}

bool ServerProtocol::finishedReceiving() const {
    return readCommand;
}

