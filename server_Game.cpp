#include "server_Game.h"
#include "common_TPException.h"
#include <iostream>
#include <string>
#include <utility>

#define INVALID_RANGE "Rango invalido"
#define REPEATED_DIGITS "Digitos repetidos"
const unsigned int MIN_NUMBER = 100, MAX_NUMBER = 999;
const unsigned int PERFECT_SCORE = 30, MAX_PLAYER_TRIES = 10;

Game::Game(unsigned int secretNumber) : finished(false), playerTries(0) {
    this->secretNumber = std::to_string(secretNumber);
}

void Game::_updateStatus(unsigned int result) {
    if (result == PERFECT_SCORE) {
        finished = true;
        ++wonGames;
    } else if (playerTries == MAX_PLAYER_TRIES) {
        finished = true;
        ++lostGames;
    }
}

void Game::_compareNumbers(unsigned int& result, std::string&& number) {
    unsigned int i = 0, j;
    for (auto & digitSN : secretNumber) {
        ++i;
        j = 0;
        for (auto & digitN : number) {
            ++j;
            if (digitN == digitSN) {
                if (i == j)
                    result += 10;
                else
                    ++result;
            }
        }
    }
}

void Game::_verifyRepeatedDigits(std::string& strNumber) {
    bool repeatedDigit = strNumber[0] == strNumber[1];
    repeatedDigit = repeatedDigit || (strNumber[0] == strNumber[2]);
    repeatedDigit = repeatedDigit || (strNumber[1] == strNumber[2]);
    if (repeatedDigit) {
        _updateStatus(0);
        throw TPException(REPEATED_DIGITS);
    }
}

/*Por cada numero bien sumo 10, regular sumo 1, mal no sumo nada*/
unsigned int Game::guess(unsigned int number) {
    unsigned int result = 0;
    ++playerTries;
    if ( (number < MIN_NUMBER) || (number > MAX_NUMBER) ) {
        _updateStatus(0);
        throw TPException(INVALID_RANGE);
    }
    std::string strNumber = std::to_string(number);
    _verifyRepeatedDigits(strNumber);
    _compareNumbers(result, std::move(strNumber));
    _updateStatus(result);
    return result;
}

bool Game::hasFinished() const {
    return finished;
}

void Game::surrender() {
    ++lostGames;
    finished = true;
}

/*Se inicializan las variables estaticas*/
std::atomic<unsigned int> Game::wonGames(0);
std::atomic<unsigned int> Game::lostGames(0);

void Game::showResults() {
    std::cout << "Estadísticas:\n\tGanadores:  " << wonGames;
    std::cout << "\n\tPerdedores: " << lostGames << std::endl;
}
