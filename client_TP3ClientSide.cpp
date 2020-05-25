#include "client_TP3ClientSide.h"
#include "client_Client.h"
#include <iostream>

#define INVALID_ARGUMENTS_MESSAGE "Error: argumentos invalidos."
#define ARGUMENT_AMOUNT 3
#define ERROR 1
#define SUCCESS 0

int TP3ClientSide::run(int argc, char** argv) {
    if (argc != ARGUMENT_AMOUNT) {
        std::cerr << INVALID_ARGUMENTS_MESSAGE << std::endl;
        return ERROR;
    }
    try {
        Client client(argv[1], argv[2]);
        client.connect();
    } catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return SUCCESS;
}
