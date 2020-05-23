#ifndef TP3TALLER_COMMON_TPEXCEPTION_H
#define TP3TALLER_COMMON_TPEXCEPTION_H

#include <exception>
#include <string>
#include <utility>

class TPException : public std::exception {
private:
    std::string errorMessage;

public:
    explicit TPException(std::string&& errorMessage) :
                                    errorMessage(std::move(errorMessage)) {}
    const char* what() const noexcept override;
};


#endif //TP3TALLER_COMMON_TPEXCEPTION_H
