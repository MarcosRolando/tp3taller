#ifndef TP3TALLER_SERVERMONITOR_H
#define TP3TALLER_SERVERMONITOR_H

/*Esta clase es la que chequea cuando cerrar el server*/

#include "Server.h"
#include "Thread.h"

class ServerMonitor : public Thread {
private:
    Server& server;
public:
    explicit ServerMonitor(Server& server) : server(server) {};

    /*Implementa la funcion run heredada de Thread, la cual para esta clase
     * correra el metodo stopOnCommand*/
    void run() override;
private:
    void _stopOnCommand();
};


#endif //TP3TALLER_SERVERMONITOR_H
