//
// Created by marcos on 22/5/20.
//

#ifndef TP3TALLER_SERVERMONITOR_H
#define TP3TALLER_SERVERMONITOR_H

/*Esta clase es la que chequea cuando cerrar el server, el nombre puede confundir
 * pero no se me ocurrio uno mejor*/

#include "Server.h"
#include "Thread.h"

class ServerMonitor : public Thread {
private:
    Server& server;
public:
    explicit ServerMonitor(Server& server) : server(server) {};
    void run() override ;
private:
    void _stopOnCommand();
};


#endif //TP3TALLER_SERVERMONITOR_H
