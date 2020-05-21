//
// Created by marcos on 7/5/20.
//

#ifndef TP2TALLER_WORKERREADER_H
#define TP2TALLER_WORKERREADER_H

#include <fstream>
#include <vector>

class FileReader {
private:
    std::string fileName;
    std::ifstream file;
    std::vector<unsigned short int> numbers;
public:
    explicit FileReader(std::string&& fileName);
private:
    void _readNumbers();
    void _verifyRepeatedDigits(std::string&& strNumber);
    void _addNumber(unsigned int short number);
};


#endif //TP2TALLER_WORKERREADER_H
