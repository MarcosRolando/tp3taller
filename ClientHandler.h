//
// Created by marcos on 20/5/20.
//

#ifndef TP3TALLER_CLIENTHANDLER_H
#define TP3TALLER_CLIENTHANDLER_H

/*Esta clase sera la que se comunique con el cliente, es decir, el servidor
 * cuando acepta a un cliente crea un nuevo ClientHandler (un estilo de
 * subservidor) y lo dispara en un nuevo thread. Esta clase guarda una instancia
 * del protocolo, que guarda una instancia independiente del Juego de Adivinar el Numero*/

#include "ServerProtocol.h"
#include "Socket.h"
#include "Thread.h"

class ClientHandler : public Thread {
private:
    Socket socket;
    ServerProtocol protocol;
    bool finished;
public:
    ClientHandler(Socket&& socket, unsigned int short secretNumber) :
        socket(std::move(socket)), protocol(secretNumber), finished(false) {};
    void run() override;
    void forceFinish();
};


#endif //TP3TALLER_CLIENTHANDLER_H
