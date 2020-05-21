cmake_minimum_required(VERSION 3.16)
project(tp3taller)

add_executable(tp main.cpp Socket.cpp Socket.h ClientHandler.cpp ClientHandler.h Game.cpp Game.h
        ServerProtocol.cpp ServerProtocol.h TPException.cpp TPException.h
        Thread.cpp Thread.h Server.cpp Server.h FileReader.cpp FileReader.h)

target_compile_options (tp PRIVATE -std=c++11 -Wall -Werror -pedantic -pedantic-errors
        -O0 -ggdb -DDEBUG -fno-inline)

target_link_options(tp PRIVATE -lm -pthread)