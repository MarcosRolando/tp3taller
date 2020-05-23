#include "ServerProtocol.h"
#include <arpa/inet.h>
#include <cstring>
#include "TPException.h"

#define HELP_MESSAGE "Comandos validos:\n\tAYUDA: despliega la lista" \
                        "de comandos validos\n\tRENDIRSE: pierde el juego" \
                        " automaticamente\n\tXXX: Numero de 3 cifras a ser " \
                        "enviado al servidor para adivinar el numero secreto"

#define LOST_MESSAGE "Perdiste"
#define WON_MESSAGE "Ganaste"
#define INVALID_NUMBER_MESSAGE "Número inválido. Debe ser de 3 cifras no " \
                                                                    "repetidas"

const char HELP_CHAR = 'h';
const char SURRENDER_CHAR = 's';
const char NUMBER_CHAR = 'n';

const unsigned char PERFECT_SCORE = 30;

void ServerProtocol::_helpCommand() {
    response = HELP_MESSAGE;
}

void ServerProtocol::_surrenderCommand() {
    game.surrender();
    response = LOST_MESSAGE;
}

void ServerProtocol::_setGuessResult(unsigned char score) {
    unsigned char firstDigit = (score / 10) % 10;
    unsigned char secondDigit = score % 10;
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
        unsigned char score = game.guess(number);
        if (game.hasFinished()) {
            if (score == PERFECT_SCORE) response = WON_MESSAGE;
            else response = LOST_MESSAGE;
        } else {
            _setGuessResult(score);
        }
    } catch (TPException& e) {
        response = INVALID_NUMBER_MESSAGE;
        if (game.hasFinished()) response = LOST_MESSAGE;
    }
}

std::unique_ptr<char[]> ServerProtocol::commandBuffer(unsigned int& bufferLength) {
    readCommand = false;
    if (!receivingNumber) {
        bufferLength = 1;
        std::unique_ptr<char[]> buffer(new char[bufferLength]());
        return buffer;
    } else {
        bufferLength = 2;
        std::unique_ptr<char[]> buffer(new char[bufferLength]());
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

std::unique_ptr<char []> ServerProtocol::getResponse(unsigned int& bufferSize) {
    uint32_t msgLength = response.length();
    bufferSize = msgLength + 4;
    std::unique_ptr<char[]> responseMsg(new char[bufferSize]());
    memset(responseMsg.get(), 0, bufferSize);
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

bool ServerProtocol::hasFinished() {
    return game.hasFinished();
}

bool ServerProtocol::finishedReceiving() const {
    return readCommand;
}

