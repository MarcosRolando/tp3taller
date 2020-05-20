//
// Created by marcos on 20/5/20.
//

#ifndef TP3TALLER_SERVERPROTOCOL_H
#define TP3TALLER_SERVERPROTOCOL_H

/*Esta clase se encarga de entender y armar los mensajes enviados desde
 * el cliente, comunicandose con el Game*/

#include "Game.h"

class ServerProtocol {
private:
    Game game;
    std::string response;
public:
    explicit ServerProtocol(unsigned short int secretNumber) : game(secretNumber) {};
    unsigned int processCommand(char* clientCommand); /*Recibe el string del comando del cliente y lo procesa*/
private:
    void helpCommand();
    void surrenderCommand();
    void numberCommand(char* clientCommand);
};


#endif //TP3TALLER_SERVERPROTOCOL_H
