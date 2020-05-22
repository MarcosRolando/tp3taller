//
// Created by marcos on 22/5/20.
//

#include "ServerMonitor.h"
#include <iostream>

void ServerMonitor::_stopOnCommand() {
    unsigned char input = 0;
    while (input != 'q') {
        std::cin >> input;
    }
    server.forceFinish();
}

void ServerMonitor::run() {
    _stopOnCommand();
}
