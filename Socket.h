//
// Created by marcos on 20/5/20.
//

#ifndef TP3TALLER_SOCKET_H
#define TP3TALLER_SOCKET_H


class Socket {
private:
    int fd; /*file descriptor*/
public:
    Socket() : fd(-1) {}; /*sobrecargo el constructor*/
    Socket(const Socket&) = delete;
    Socket operator=(const Socket&) = delete;
    Socket& operator=(Socket&&);
    Socket(Socket&& srcSocket) noexcept;
    void connect(struct addrinfo* addresses);
    void bind(struct addrinfo* addresses);
    void maxListen(int max) const;
    Socket accept() const;
    ~Socket();
private:
    explicit Socket(int fd) : fd(fd) {};
};


#endif //TP3TALLER_SOCKET_H
