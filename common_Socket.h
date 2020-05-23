#ifndef TP3TALLER_COMMON_SOCKET_H
#define TP3TALLER_COMMON_SOCKET_H

#include <cstdio>

class Socket {
private:
    int fd; /*File Descriptor*/

public:
    Socket() : fd(-1) {}
    Socket(const Socket&) = delete; /*Borro los constructores por copia*/
    Socket operator=(const Socket&) = delete;
    Socket& operator=(Socket&&) noexcept;
    Socket(Socket&& srcSocket) noexcept;

    /*Conecta el cliente al servidor*/
    void connect(struct addrinfo* addresses);

    /*Acepta una nueva conexion, retornando el socket generado*/
    Socket accept() const;

    /*Bindea a un socket*/
    void bind(struct addrinfo* addresses);

    /*Setea la cantidad maxima de clientes que se tendran en espera*/
    void maxListen(int max) const;

    /*Envia el mensaje*/
    void send(char* message, size_t length) const;

    /*Recibe el mensaje*/
    void receive(char* message, size_t length) const;

    /*Cierra el socket*/
    void close();
    ~Socket();

private:
    explicit Socket(int fd) : fd(fd) {}
};


#endif //TP3TALLER_COMMON_SOCKET_H
