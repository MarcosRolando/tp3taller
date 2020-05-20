//
// Created by marcos on 20/5/20.
//

#include "ServerProtocol.h"
#include <iostream>
void ServerProtocol::helpCommand() {
    response = "Comandos validos:\n\tAYUDA: despliega la lista"
                          "de comandos validos\n\tRENDIRSE: pierde el juego"
                          "automaticamente\n\tXXX: Numero de 3 cifras a ser "
                          "enviado al servidor para adivinar el numero secreto";
}

void ServerProtocol::surrenderCommand() {
    Game::surrender();
    response = "Perdiste";
}

void ServerProtocol::numberCommand(char* clientCommand) {
    unsigned short int number = *(reinterpret_cast<unsigned short int*>(clientCommand));
    unsigned char score = game.guess(number);
    std::string strScore = std::to_string(score);
    for (auto & digit : strScore) {
        std::cout << digit;
    }
}

/*Retorna la cantidad de bytes que tiene que leer el ClientHandler*/
unsigned int ServerProtocol::processCommand(char* clientCommand) {
    unsigned int bytesToRead = 0;
    if (receivingNumber) { /*patch por si el byte coincide con las letras xd*/
        numberCommand(clientCommand);
        receivingNumber = false;
    } else if (*clientCommand == 'h') {
        helpCommand();
    } else if (*clientCommand == 's') {
        surrenderCommand();
    } else if (*clientCommand == 'n') {
        bytesToRead = 2; /*tiene que leer 2 bytes*/
        receivingNumber = true;
    }
    return bytesToRead; /*lei el mensaje entero*/
}
