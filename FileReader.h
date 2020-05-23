#ifndef TP3TALLER_FILEREADER_H
#define TP3TALLER_FILEREADER_H

/*Esta clase se encarga de leer los numeros del archivo, retornando los numeros
 * en Round Robin*/

#include <fstream>
#include <vector>

class FileReader {
private:
    std::ifstream file;
    std::vector<unsigned short> numbers;
    std::vector<unsigned short>::iterator currentNumber;
public:
    explicit FileReader(std::string&& fileName);

    /*Retorna el siguiente numero del archivo acorde a Round Robin*/
    unsigned short getNextNumber();
private:
    void _readNumbers();
    static void _verifyRepeatedDigits(std::string&& strNumber);
    void _addNumber(unsigned short number);
};


#endif //TP3TALLER_FILEREADER_H
