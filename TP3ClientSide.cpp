#include "TP3ClientSide.h"
#include "Client.h"
#include <iostream>

#define INVALID_ARGUMENTS_MESSAGE "Error: argumentos invalidos."

int TP3ClientSide::run(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << INVALID_ARGUMENTS_MESSAGE << std::endl;
        return 1;
    }
    try {
        Client client(argv[1], argv[2]);
        client.connect();
    } catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
