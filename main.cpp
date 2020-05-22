#include "Server.h"
#include "FileReader.h"
#include "TPException.h"
#include "Client.h"
#include <iostream>
int main(int argc, char** argv) {
    std::string mode = argv[1];
    if (mode == "server") {
        Server server("8080", "numeros");
        server.connect();
    } else if (mode == "client") {
        Client client("localhost", "8080");
        client.connect();
    } else {
        std::cout << "Le pifiaste el modo capo" << std::endl;
    }
    /*
    ServerProtocol protocol(124);
    unsigned short int number = 200;
    char* n = reinterpret_cast<char*>(&number);
    protocol.processCommand(n);
    unsigned int buffSize;
    std::unique_ptr<char []> message = protocol.getResponse(buffSize);
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
