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
    bool receivingNumber, readCommand;
public:
    explicit ServerProtocol(unsigned short secretNumber) : game(secretNumber),
                                receivingNumber(false), readCommand(false){};

    /*Recibe el buffer con el comando enviado por el cliente y lo descifra*/
    void processCommand(const char* clientCommand);

    /*Retorna el buffer para recibir el mensaje junto con su longitud*/
    std::unique_ptr<char[]> commandBuffer(unsigned int& bufferLength);

    /*Retorna el buffer con la respuesta al request del cliente y la
     * longitud del mismo*/
    std::unique_ptr<char[]> getResponse(unsigned int& bufferSize);

    /*Retorna si el protocolo recibio el mensaje del entero del cliente*/
    bool finishedReceiving() const;

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
