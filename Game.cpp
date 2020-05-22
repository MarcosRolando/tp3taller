//
// Created by marcos on 20/5/20.
//

#include "Game.h"
#include "TPException.h"

Game::Game(unsigned short int secretNumber) : finished(false), playerTries(0) {
    this->secretNumber = std::to_string(secretNumber);
}

void Game::_updateStatus(unsigned char result) {
    playerTries++;
    if (result == 30) {
        finished = true;
        wonGames++;
    } else if (playerTries == 10) {
        finished = true;
        lostGames++;
    }
}

void Game::_compareNumbers(unsigned char& result, std::string&& number) {
    unsigned char i = 0, j;
    for (auto & digitSN : secretNumber) {
        ++i;
        j = 0;
        for (auto & digitN : number) {
            ++j;
            if (digitN == digitSN) {
                if (i == j) result += 10;
                else result++;
            }
        }
    }
}

void Game::_verifyRepeatedDigits(std::string& strNumber) {
    if (strNumber[0] == strNumber[1]) throw TPException("Digitos repetidos");
    if (strNumber[0] == strNumber[2]) throw TPException("Digitos repetidos");
    if (strNumber[1] == strNumber[2]) throw TPException("Digitos repetidos");
}

/*Por cada numero bien sumo 10, regular sumo 1, mal no sumo nada*/
unsigned char Game::guess(unsigned short int number) { //con un char me alcanza
    if ( (number < 100) || (number > 999) )
        throw TPException("Rango invalido");
    std::string strNumber = std::to_string(number);
    _verifyRepeatedDigits(strNumber);
    unsigned char result = 0;
    _compareNumbers(result, std::move(strNumber));
    _updateStatus(result);
    return result;
}

bool Game::hasFinished() const {
    return finished;
}

void Game::surrender() {
    lostGames++;
    finished = true;
}

std::atomic<unsigned int> Game::wonGames{0}; /*Asi se inicializan las variables estaticas*/
std::atomic<unsigned int> Game::lostGames{0};

/*Segun la documentacion esto se hace antes de llamar al main por lo tanto es THREAD SAFE*/