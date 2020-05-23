cmake_minimum_required(VERSION 3.16)
project(tp3taller)

add_executable(server Socket.cpp Socket.h ClientHandler.cpp ClientHandler.h Game.cpp Game.h
        ServerProtocol.cpp ServerProtocol.h TPException.cpp TPException.h
        Thread.cpp Thread.h Server.cpp Server.h FileReader.cpp FileReader.h
        OSException.h ServerMonitor.cpp ServerMonitor.h OSException.cpp
        GameProtocolConstants.h serverMain.cpp TP3ServerSide.cpp TP3ServerSide.h)

add_executable(client clientMain.cpp Socket.cpp Socket.h TPException.cpp TPException.h
        Thread.cpp Thread.h Client.cpp Client.h ClientProtocol.cpp ClientProtocol.h User.cpp User.h
        OSException.h OSException.cpp GameProtocolConstants.h TP3ClientSide.cpp TP3ClientSide.h)


target_compile_options (server PRIVATE -std=c++11 -Wall -Werror -pedantic -pedantic-errors
        -O0 -ggdb -DDEBUG -fno-inline)

target_link_options(server PRIVATE -lm -pthread)

target_compile_options (client PRIVATE -std=c++11 -Wall -Werror -pedantic -pedantic-errors
        -O0 -ggdb -DDEBUG -fno-inline)

target_link_options(client PRIVATE -lm -pthread)