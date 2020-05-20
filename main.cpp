#include "Game.h"
#include <iostream>
int main() {
    Game game(124);
    while (!game.hasFinished()) {
        int number;
        std::cin >> number;
        int result = game.guess(number);
        std::cout << result << std::endl;
    }
    return 0;
}
