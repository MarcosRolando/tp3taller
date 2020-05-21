//
// Created by marcos on 20/5/20.
//

#include "ServerProtocol.h"
#include <arpa/inet.h>
#include <cstring>
#include "TPException.h"

void ServerProtocol::_helpCommand() {
    response = "Comandos validos:\n\tAYUDA: despliega la lista"
                          "de comandos validos\n\tRENDIRSE: pierde el juego"
                          " automaticamente\n\tXXX: Numero de 3 cifras a ser "
                          "enviado al servidor para adivinar el numero secreto";
}

void ServerProtocol::_surrenderCommand() {
    game.surrender();
    response = "Perdiste";
}

void ServerProtocol::_setGuessResult(unsigned char firstDigit, unsigned char secondDigit) {
    response.clear();
    if (firstDigit == 0 && secondDigit == 0) {
        response += "3 mal";
    } if (firstDigit != 0) {
        response += std::to_string(firstDigit) + " bien";
        if (secondDigit != 0) response += ", " + std::to_string(secondDigit) + " regular";
    } else if (secondDigit != 0) {
        response += std::to_string(secondDigit) + " regular";
    }
}

void ServerProtocol::_numberCommand(const char* clientCommand) {
    unsigned short int number = *(reinterpret_cast<const unsigned short int*>(clientCommand));
    number = ntohs(number);
    try {
        unsigned char score = game.guess(number);
        if (game.hasFinished()) {
            if (score == 30) response = "Ganaste";
            else response = "Perdiste";
        } else {
            unsigned char firstDigit = (score / 10) % 10;
            unsigned char secondDigit = score % 10;
            _setGuessResult(firstDigit, secondDigit);
        }
    } catch (TPException& e) {
        response = "Número inválido. Debe ser de 3 cifras no repetidas";
    }

}

/*Retorna la cantidad de bytes que tiene que leer el ClientHandler*/
unsigned int ServerProtocol::processCommand(const char* clientCommand) {
    unsigned int bytesToRead = 0;
    if (receivingNumber) { /*patch por si el byte coincide con las letras xd*/
        _numberCommand(clientCommand);
        receivingNumber = false;
    } else if (*clientCommand == 'h') {
        _helpCommand();
    } else if (*clientCommand == 's') {
        _surrenderCommand();
    } else if (*clientCommand == 'n') {
        bytesToRead = 2; /*tiene que leer 2 bytes*/
        receivingNumber = true;
    }
    return bytesToRead; /*lei el mensaje entero*/
}

std::unique_ptr<char []> ServerProtocol::getResponse(unsigned int& bufferSize) {
    unsigned int msgLength = response.length();
    bufferSize = msgLength + 5;
    std::unique_ptr<char []> responseMsg(new char[bufferSize]()); /*4 bytes del largo, 1 byte del \0*/
    memset(responseMsg.get(), 0, bufferSize);
    responseMsg[bufferSize - 1] = '\0';
    msgLength = htonl(msgLength);
    for (int i = 0; i < 4; ++i) {
        responseMsg[i] = *(reinterpret_cast<char*>(&msgLength) + i);
    }
    unsigned int i = 4;
    for (auto & c : response) {
        responseMsg[i] = c;
        ++i;
    }
    return responseMsg;
}

bool ServerProtocol::hasFinished() {
    return game.hasFinished();
}

