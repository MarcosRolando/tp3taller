//
// Created by marcos on 20/5/20.
//

#ifndef TP3TALLER_SOCKET_H
#define TP3TALLER_SOCKET_H

#include <cstdio>

class Socket {
private:
    int fd; /*file descriptor*/
public:
    Socket() : fd(-1) {}; /*sobrecargo el constructor*/
    Socket(const Socket&) = delete;
    Socket operator=(const Socket&) = delete;
    Socket& operator=(Socket&&) noexcept;
    Socket(Socket&& srcSocket) noexcept;
    void connect(struct addrinfo* addresses);
    void bind(struct addrinfo* addresses);
    void maxListen(int max) const;
    void send(char* message, size_t length) const;
    void receive(char* message, size_t length) const;
    Socket accept() const;
    ~Socket();
private:
    explicit Socket(int fd) : fd(fd) {};
};


#endif //TP3TALLER_SOCKET_H
