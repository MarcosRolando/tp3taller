#ifndef TP3TALLER_OSEXCEPTION_H
#define TP3TALLER_OSEXCEPTION_H

#include <exception>
#define BUF_LEN 256

class OSException : std::exception {
private:
    int _errno;
    char errorMsg[BUF_LEN]{};
public:
    explicit OSException(const char* fmt, ...) noexcept;
    const char * what() const noexcept override;
};

#endif //TP3TALLER_OSEXCEPTION_H
