#include "TP3ServerSide.h"
#include "Server.h"
#include <iostream>
#include "Game.h"

#define INVALID_ARGUMENTS_MESSAGE "Error: argumentos invalidos."

int TP3ServerSide::run(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << INVALID_ARGUMENTS_MESSAGE << std::endl;
        return 0;
    }
    try {
        Server server(argv[1], argv[2]);
        server.connect();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    Game::showResults();
    return 0;
}
