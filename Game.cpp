//
// Created by marcos on 20/5/20.
//

#include "Game.h"

Game::Game(unsigned short int secretNumber) : finished(false), playerTries(0) {
    this->secretNumber = std::to_string(secretNumber);
}
/*
std::string Game::help() {
    std::string helpMsg = "Comandos validos:\n\tAYUDA: despliega la lista" Falta poner tildes
                          //"de comandos validos\n\tRENDIRSE: pierde el juego"
                          //"automaticamente\n\tXXX: Numero de 3 cifras a ser "
                          //"enviado al servidor para adivinar el numero secreto";
    //return helpMsg;
}
*//*ESTO VA EN EL PROTOCOLO, NO QUIERO QUE EL JUEGO GENERE NADA DE TEXTO*/
void Game::updateStatus(unsigned char result) {
    playerTries++;
    if (result == 30) {
        finished = true;
        wonGames++;
    } else if (playerTries == 10) {
        finished = true;
        lostGames++;
    }
}

/*Por cada numero bien sumo 10, regular sumo 1, mal no sumo nada*/
unsigned char Game::guess(unsigned short int number) { //con un char me alcanza
    unsigned char result = 0, i = 0, j;
    std::string strNumber = std::to_string(number);
    for (auto & digitSN : secretNumber) {
        ++i;
        j = 0;
        for (auto & digitN : strNumber) {
            ++j;
            if (digitN == digitSN) {
                if (i == j) result += 10;
                else result++;
            }
        }
    }
    updateStatus(result);
    return result;
}

bool Game::hasFinished() const {
    return finished;
}

void Game::surrender() {
    lostGames++;
}

std::atomic<unsigned int> Game::wonGames{0}; /*Asi se inicializan las variables estaticas*/
std::atomic<unsigned int> Game::lostGames{0};

/*Segun la documentacion esto se hace antes de llamar al main por lo tanto es THREAD SAFE*/