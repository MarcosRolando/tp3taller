#include "Server.h"
#include "FileReader.h"
#include "TPException.h"
#include <iostream>
#include "ClientProtocol.h"
int main() {
    /*
    ServerProtocol protocol(124);
    unsigned short int number = 200;
    char* n = reinterpret_cast<char*>(&number);
    protocol.processCommand(n);
    unsigned int buffSize;
    std::unique_ptr<char []> message = protocol.getResponse(buffSize);
     */
    /*
    Server server("8080");
    server.connect();
     */
    /*
    try {
        FileReader file("server.list");
    } catch (TPException& e) {
        std::cout << e.what();
    }
     */
    return 0;
}
