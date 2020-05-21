//
// Created by marcos on 20/5/20.
//

#include "Socket.h"
#include <netdb.h>
#include <unistd.h>

void Socket::connect(struct addrinfo* addresses) {
struct addrinfo* rp;
    for (rp = addresses; rp != nullptr; rp = rp->ai_next) {
        this->fd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (this->fd  == -1)
            continue;

        if (::connect(this->fd , rp->ai_addr, rp->ai_addrlen) != -1)
            break;                  /* Success */

        close(this->fd);
    }
    //chequear por error y tirar exception
}

void Socket::bind(struct addrinfo* addresses) {
    struct addrinfo* rp;
    int val = 1; //no entiendo esto pero el dipa lo hace
    for (rp = addresses; rp != nullptr; rp = rp->ai_next) {
        fd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (this->fd == -1)
            continue;

        setsockopt(this->fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

        if (::bind(this->fd, rp->ai_addr, rp->ai_addrlen) == 0)
            break;                  /* Success */

        close(this->fd);
    }
    //chequear por error y tirar exception
}

Socket Socket::accept() const {
    int peerFd = ::accept(fd, nullptr, nullptr);
    Socket peer(peerFd);
    return peer;
}

void Socket::send(char* message, size_t length) const {
    size_t bytesSent = 0;
    int s = 0;

    while (bytesSent < length) {
        s = ::send(fd, message + bytesSent, length - bytesSent, MSG_NOSIGNAL);
        //chequear error y tirar exception
        bytesSent += s;
    }
}

void Socket::receive(char* message, size_t length) const {
    size_t bytesReceived = 0;
    int s = 0;

    while (bytesReceived < length) {
        s = recv(fd, message + bytesReceived, length - bytesReceived, 0);
        //chequear error y tirar exception, s == -1
        if (s == 0) break;
        bytesReceived += s;
    }
}

void Socket::maxListen(int max) const {
    listen(fd, 20);
}

Socket::~Socket() {
    if (fd != -1) {
        shutdown(fd, SHUT_RDWR);
        close(fd);
        fd = -1;
    }
}

Socket::Socket(Socket&& srcSocket) noexcept {
    fd = srcSocket.fd;
    srcSocket.fd = -1; /*le robo el fd y le dejo uno inutil*/
}

Socket& Socket::operator=(Socket&& srcSocket) noexcept {
    fd = srcSocket.fd;
    srcSocket.fd = -1; /*le robo el fd y le dejo uno inutil*/
    return *this;
}