//
// Created by marcos on 20/5/20.
//

#ifndef TP3TALLER_SERVERPROTOCOL_H
#define TP3TALLER_SERVERPROTOCOL_H

/*Esta clase se encarga de entender y armar los mensajes enviados desde
 * el cliente, comunicandose con el Game*/

#include "Game.h"
#include <memory>

class ServerProtocol {
private:
    Game game;
    std::string response;
    bool receivingNumber;
public:
    explicit ServerProtocol(unsigned short int secretNumber) : game(secretNumber), receivingNumber(false) {};
    unsigned int processCommand(const char* clientCommand); /*Recibe el string del comando del cliente y lo procesa*/
    std::unique_ptr<char []> getResponse(unsigned int& bufferSize);
    bool hasFinished();
private:
    void _helpCommand();
    void _surrenderCommand();
    void _numberCommand(const char* clientCommand);
    void _setGuessResult(unsigned char firstDigit, unsigned char secondDigit);
};


#endif //TP3TALLER_SERVERPROTOCOL_H
