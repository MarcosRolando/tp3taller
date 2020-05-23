#include "Server.h"
#include "TPException.h"
#include "Client.h"
#include <iostream>
#include "OSException.h"
int main(int argc, char** argv) {
    std::string mode = argv[1];
    if (mode == "server") {
        try {
            Server server("8081", "server.list");
            server.connect();
        } catch (OSException& e) {
            std::cout << e.what() << std::endl;
        }

    } else if (mode == "client") {
        try {
            Client client("localhost", "8081");
            client.connect();
        } catch (OSException& e) {
            std::cout << e.what() << std::endl;
        }

    } else {
        std::cout << "Le pifiaste el modo capo" << std::endl;
    }
    return 0;
}
