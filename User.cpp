//
// Created by marcos on 21/5/20.
//

#include "User.h"
#include <iostream>
#include <string>

std::string User::getInput() {
    std::string input;
    std::getline(std::cin, input);
    return input;
}

void User::showResponse(std::unique_ptr<char[]> message) {
    std::cout << message.get();
}
