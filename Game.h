#ifndef TP3TALLER_GAME_H
#define TP3TALLER_GAME_H

/*Esta clase contiene la logica del juego Adivina el Numero, instanciandose
 * una por cada cliente que se conecte*/

#include <string>
#include <atomic>

class Game {
private:
    bool finished;
    std::string secretNumber;
    unsigned int playerTries;
    static std::atomic<unsigned int> wonGames, lostGames;
public:
    explicit Game(unsigned int secretNumber);

    /*Compara el numero que ingreso el cliente con el numero secreto y retorna
     * una puntuacion donde se asignan 10 puntos por digito correcto y 1
     * punto por digito regular. Los mal no suman puntos*/
    unsigned int guess(unsigned int number);

    /*Termina el juego y computa una derrota*/
    void surrender();

    /*Retorna si el juego ha o no terminado*/
    bool hasFinished() const;

    /*Muestra por stdout los resultados de las partidas*/
    static void showResults();
private:
    void _updateStatus(unsigned int result);
    void _compareNumbers(unsigned int& result, std::string&& number);
    void _verifyRepeatedDigits(std::string& strNumber);
};

#endif //TP3TALLER_GAME_H
