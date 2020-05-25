#ifndef TP3TALLER_COMMON_OSEXCEPTION_H
#define TP3TALLER_COMMON_OSEXCEPTION_H

/*Esta clase maneja los posibles errores en getaddrinfo y el socket*/

#include <exception>
#define BUF_LEN 256

class OSException : public std::exception {
private:
    int _errno;
    char errorMsg[BUF_LEN];
public:
    explicit OSException(const char* fmt, ...) noexcept;
    const char * what() const noexcept override;
};

#endif //TP3TALLER_COMMON_OSEXCEPTION_H
