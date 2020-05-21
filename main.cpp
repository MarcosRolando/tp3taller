#include "ServerProtocol.h"
#include "Server.h"
int main() {
    /*
    ServerProtocol protocol(124);
    unsigned short int number = 200;
    char* n = reinterpret_cast<char*>(&number);
    protocol.processCommand(n);
    unsigned int buffSize;
    std::unique_ptr<char []> message = protocol.getResponse(buffSize);
     */
    Server server("8080");
    server.connect();
    return 0;
}
