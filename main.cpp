#include "ServerProtocol.h"
#include <iostream>
int main() {
    ServerProtocol protocol(124);
    unsigned short int number = 200;
    char* n = reinterpret_cast<char*>(&number);
    protocol.processCommand(n);
    /*
    char msg[1] = {'h'};
    protocol.processCommand(msg);
     */
    std::unique_ptr<char []> message = protocol.getResponse();
    return 0;
}
