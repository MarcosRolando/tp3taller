#include "Game.h"
#include "ServerProtocol.h"
int main() {
    ServerProtocol protocol(124);
    unsigned short int number = 208;
    char* n = reinterpret_cast<char*>(&number);
    protocol.processCommand(n);
    return 0;
}
