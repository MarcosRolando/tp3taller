//
// Created by marcos on 20/5/20.
//

#ifndef TP3TALLER_GAME_H
#define TP3TALLER_GAME_H

/*Esta clase contiene la logica del juego Adivina el Numero, y se instanciara
 * una por cada cliente que se conecte para simplificar el problema y mejorar la
 * eficiencia de performance evitando compartir recursos*/

#include <string>

class Game {
private:
    unsigned short int secretNumber; /*el numero siempre sera valido, lo verifica el FileReader*/
    unsigned char playerTries; /*solo son 10 intentos asi que el char me alcanza*/
    static unsigned int wonGames, lostGames; //comun a todos los juegos, puede ser que no lo haga static despues, ver bien, PROTEGER DE RC!
public:
    explicit Game(unsigned int secretNumber) : secretNumber(secretNumber),
                                                playerTries(0) {};
    std::string help();
};

#endif //TP3TALLER_GAME_H
