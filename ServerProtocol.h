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
    explicit ServerProtocol(unsigned short secretNumber) : game(secretNumber),
                                                    receivingNumber(false) {};

    /*Recibe el buffer con el comando enviado por el cliente y lo descifra*/
    unsigned int processCommand(const char* clientCommand);

    /*Retorna el buffer con la respuesta al request del cliente y la
     * longitud del mismo*/
    std::unique_ptr<char[]> getResponse(unsigned int& bufferSize);

    /*Retorna si la comunicacion se ha dado por finalizada, que para este TP
     * es cuando el juego se termina*/
    bool hasFinished();
private:
    void _helpCommand();
    void _surrenderCommand();
    void _numberCommand(const char* clientCommand);
    void _setGuessResult(unsigned char score);
};


#endif //TP3TALLER_SERVERPROTOCOL_H
