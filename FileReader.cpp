//
// Created by marcos on 7/5/20.
//

#include "FileReader.h"
#include "TPException.h"

FileReader::FileReader(std::string&& fileName)  :
                                            fileName(fileName), file(fileName) {
    if (!this->file.is_open()) throw TPException("El archivo" +
    fileName + "no se encuentra en el directorio del ejecutable o no existe");
    _readNumbers();
    currentNumber = numbers.begin();
}

void FileReader::_verifyRepeatedDigits(std::string&& strNumber) {
    if (strNumber[0] == strNumber[1]) throw TPException("Digitos repetidos");
    if (strNumber[0] == strNumber[2]) throw TPException("Digitos repetidos");
    if (strNumber[1] == strNumber[2]) throw TPException("Digitos repetidos");
}

void FileReader::_readNumbers() {
    std::string strNumber;
    unsigned int short number;
    while (!file.eof()) {
        std::getline(file, strNumber);
        try {
            number = std::stoi(strNumber);
            _verifyRepeatedDigits(std::move(strNumber));
        } catch (std::invalid_argument& e) {
            throw TPException("El archivo debe contener numeros unicamente");
        }
        _addNumber(number);
    }
}

void FileReader::_addNumber(unsigned int short number) {
    if ( (number < 100) || (number > 999) )
        throw TPException("Error: archivo con números fuera de rango");
    numbers.push_back(number);
}

unsigned short int FileReader::getNextNumber() {
    if (currentNumber == numbers.end()) currentNumber = numbers.begin();
    unsigned short int n = *currentNumber;
    currentNumber++;
    return n;
}

