//
// Created by marcos on 21/5/20.
//

#ifndef TP3TALLER_USER_H
#define TP3TALLER_USER_H

#include <string>
#include <memory>

class User {
public:
    static std::string getInput();
    static void showResponse(std::unique_ptr<char[]> message);
};


#endif //TP3TALLER_USER_H
