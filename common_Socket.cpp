#include "common_Socket.h"
#include <netdb.h>
#include <unistd.h>
#include "common_OSException.h"

void Socket::connect(struct addrinfo* addresses) {
struct addrinfo* rp;
    for (rp = addresses; rp != nullptr; rp = rp->ai_next) {
        fd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (fd  == -1)
            continue;

        if (::connect(fd , rp->ai_addr, rp->ai_addrlen) != -1)
            break; /*Logre conectarme*/

        ::close(fd);
    }
    if (rp == nullptr) throw OSException("Could not connect. ");
}

void Socket::bind(struct addrinfo* addresses) {
    struct addrinfo* rp;
    int val = 1;
    for (rp = addresses; rp != nullptr; rp = rp->ai_next) {
        fd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
        if (fd == -1)
            continue;

        setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

        if (::bind(fd, rp->ai_addr, rp->ai_addrlen) == 0)
            break; /*Logre bindear*/

        ::close(fd);
    }
    if (rp == nullptr) throw OSException("Could not bind. ");
}

Socket Socket::accept() const {
    int peerFd = ::accept(fd, nullptr, nullptr);
    if (peerFd == -1) {
        throw OSException("Error in accept: %s\n");;
    }
    return Socket(peerFd);
}

void Socket::send(char* message, size_t length) const {
    size_t bytesSent = 0;
    int s = 0;

    while (bytesSent < length) {
        s = ::send(fd, message + bytesSent, length - bytesSent, MSG_NOSIGNAL);
        if (s < 1) throw OSException("Error in send: %s\n");
        bytesSent += s;
    }
}

void Socket::receive(char* message, size_t length) const {
    size_t bytesReceived = 0;
    int s = 0;

    while (bytesReceived < length) {
        s = recv(fd, message + bytesReceived, length - bytesReceived, 0);
        if (s < 1) throw OSException("Error in recv: %s\n");
        bytesReceived += s;
    }
}

void Socket::maxListen(int max) const {
    listen(fd, max);
}

Socket::~Socket() {
    close();
}

Socket::Socket(Socket&& srcSocket) noexcept {
    fd = srcSocket.fd;
    srcSocket.fd = -1;
}

Socket& Socket::operator=(Socket&& srcSocket) noexcept {
    fd = srcSocket.fd;
    srcSocket.fd = -1;
    return *this;
}

void Socket::close() {
    if (fd != -1) {
        shutdown(fd, SHUT_RDWR);
        ::close(fd);
        fd = -1;
    }
}
