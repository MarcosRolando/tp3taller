#include "server_TP3ServerSide.h"
#include "server_Server.h"
#include <iostream>
#include "server_Game.h"

#define INVALID_ARGUMENTS_MESSAGE "Error: argumentos invalidos."
#define ARGUMENT_AMOUNT 3

int TP3ServerSide::run(int argc, char** argv) {
    if (argc != ARGUMENT_AMOUNT) {
        std::cerr << INVALID_ARGUMENTS_MESSAGE << std::endl;
        return 0;
    }
    try {
        Server server(argv[1], argv[2]);
        server.connect();
        Game::showResults();
    } catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
