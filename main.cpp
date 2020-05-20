#include "Game.h"
#include <iostream>
int main() {
    Game game(124);
    int result = game.guess(569);
    std::cout << result << std::endl;
    return 0;
}
