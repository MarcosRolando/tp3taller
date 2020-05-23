#include "FileReader.h"
#include "TPException.h"

#define OUT_OF_RANGE "Error: archivo con números fuera de rango"
#define BAD_FORMAT "Error: el archivo debe contener numeros unicamente"
#define REPEATED_DIGITS "Digitos repetidos"
const unsigned short MIN_NUMBER = 100, MAX_NUMBER = 999;

FileReader::FileReader(std::string&& fileName) : file(fileName) {
    if (!this->file.is_open()) throw TPException("El archivo " +
    fileName + " no se encuentra en el directorio del ejecutable o no existe");
    _readNumbers();
    currentNumber = numbers.begin();
}

void FileReader::_verifyRepeatedDigits(std::string&& strNumber) {
    if (strNumber[0] == strNumber[1]) throw TPException(REPEATED_DIGITS);
    if (strNumber[0] == strNumber[2]) throw TPException(REPEATED_DIGITS);
    if (strNumber[1] == strNumber[2]) throw TPException(REPEATED_DIGITS);
}

void FileReader::_readNumbers() {
    std::string strNumber;
    unsigned short number;
    while (!file.eof()) {
        std::getline(file, strNumber);
        try {
            number = std::stoi(strNumber);
            _verifyRepeatedDigits(std::move(strNumber));
        } catch (std::invalid_argument& e) {
            throw TPException(BAD_FORMAT);
        }
        _addNumber(number);
    }
}

void FileReader::_addNumber(unsigned short number) {
    if ( (number < MIN_NUMBER) || (number > MAX_NUMBER) )
        throw TPException(OUT_OF_RANGE);
    numbers.push_back(number);
}

unsigned short FileReader::getNextNumber() {
    if (currentNumber == numbers.end()) currentNumber = numbers.begin();
    unsigned short n = *currentNumber;
    ++currentNumber;
    return n;
}

