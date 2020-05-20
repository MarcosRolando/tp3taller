//
// Created by marcos on 20/5/20.
//

#include "Game.h"

std::string Game::help() {
    std::string helpMsg = "Comandos validos:\n\tAYUDA: despliega la lista" /*Falta poner tildes*/
                          "de comandos validos\n\tRENDIRSE: pierde el juego"
                          "automaticamente\n\tXXX: Numero de 3 cifras a ser "
                          "enviado al servidor para adivinar el numero secreto";
    return helpMsg;
}

unsigned int Game::wonGames = 0; /*Asi se inicializan las variables estaticas*/
unsigned int Game::lostGames = 0; /*Segun la documentacion esto se hace antes de llamar al main por lo tanto es THREAD SAFE*/