//
// Created by marcos on 20/5/20.
//

#ifndef TP3TALLER_TPEXCEPTION_H
#define TP3TALLER_TPEXCEPTION_H

#include <exception>
#include <string>

/*por ahora no le meto nada, desarrollarla despues!*/
class TPException : public std::exception {
private:
    std::string errorMessage;
public:
    explicit TPException(std::string&& errorMessage) : errorMessage(std::move(errorMessage)) {};
    const char* what() const noexcept override;
};


#endif //TP3TALLER_TPEXCEPTION_H
