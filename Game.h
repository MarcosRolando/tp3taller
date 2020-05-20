//
// Created by marcos on 20/5/20.
//

#ifndef TP3TALLER_GAME_H
#define TP3TALLER_GAME_H

/*Esta clase contiene la logica del juego Adivina el Numero, y se instanciara
 * una por cada cliente que se conecte para simplificar el problema y mejorar la
 * eficiencia de performance evitando compartir recursos*/

#include <string>
#include <atomic>

class Game {
private:
    bool finished;
    std::string secretNumber; /*el numero siempre sera valido, lo verifica el FileReader*/
    unsigned char playerTries; /*solo son 10 intentos asi que el char me alcanza*/
    static std::atomic<unsigned int> wonGames, lostGames; //comun a todos los juegos, puede ser que no lo haga static despues
public:
    explicit Game(unsigned short int secretNumber);
    unsigned char guess(unsigned short int number);
    std::string help();
    static std::string surrender();
    bool hasFinished();
private:
    void updateStatus(unsigned char result);
};

#endif //TP3TALLER_GAME_H
