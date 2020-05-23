#include "Game.h"
#include "TPException.h"

#define INVALID_RANGE "Rango invalido"
#define REPEATED_DIGITS "Digitos repetidos"
const unsigned short MIN_NUMBER = 100, MAX_NUMBER = 999;
const unsigned char PERFECT_SCORE = 30, MAX_PLAYER_TRIES = 10;

Game::Game(unsigned short secretNumber) : finished(false), playerTries(0) {
    this->secretNumber = std::to_string(secretNumber);
}

void Game::_updateStatus(unsigned char result) {
    playerTries++;
    if (result == PERFECT_SCORE) {
        finished = true;
        ++wonGames;
    } else if (playerTries == MAX_PLAYER_TRIES) {
        finished = true;
        ++lostGames;
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
                else ++result;
            }
        }
    }
}

void Game::_verifyRepeatedDigits(std::string& strNumber) {
    if (strNumber[0] == strNumber[1]) throw TPException(REPEATED_DIGITS);
    if (strNumber[0] == strNumber[2]) throw TPException(REPEATED_DIGITS);
    if (strNumber[1] == strNumber[2]) throw TPException(REPEATED_DIGITS);
}

/*Por cada numero bien sumo 10, regular sumo 1, mal no sumo nada*/
unsigned char Game::guess(unsigned short number) {
    if ( (number < MIN_NUMBER) || (number > MAX_NUMBER) )
        throw TPException(INVALID_RANGE);
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
    ++lostGames;
    finished = true;
}

/*Se inicializan las variables estaticas*/
std::atomic<unsigned int> Game::wonGames{0};
std::atomic<unsigned int> Game::lostGames{0};