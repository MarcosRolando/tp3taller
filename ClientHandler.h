#ifndef TP3TALLER_CLIENTHANDLER_H
#define TP3TALLER_CLIENTHANDLER_H

/*Esta clase se comunica con el cliente, es decir, el servidor
 * cuando acepta a un cliente crea un nuevo ClientHandler (un estilo de
 * subservidor) y lo dispara en un nuevo thread. Esta clase guarda una instancia
 * del protocolo, que guarda una instancia independiente del Juego de Adivinar
 * el Numero*/

#include "ServerProtocol.h"
#include "Socket.h"
#include "Thread.h"

class ClientHandler : public Thread {
private:
    Socket socket;
    ServerProtocol protocol;
    std::atomic<bool> finished;
public:
    ClientHandler(Socket&& socket, unsigned int secretNumber) :
        socket(std::move(socket)), protocol(secretNumber), finished(false) {};

    /*Implementa el metodo virtual run de Thread, que sera el metodo ejecutado
     * por el thread*/
    void run() override;

    /*Retorna si el ha terminado de comunicarse con su cliente*/
    bool hasFinished();
private:
    void _receive(std::unique_ptr<char[]>& message,
                                            unsigned int& bufferLength);
    void _send(std::unique_ptr<char[]>& message,
                                            unsigned int& bufferLength);
};


#endif //TP3TALLER_CLIENTHANDLER_H
