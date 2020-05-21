//
// Created by marcos on 21/5/20.
//

#ifndef TP3TALLER_CLIENTPROTOCOL_H
#define TP3TALLER_CLIENTPROTOCOL_H

/*Arma los mensajes para enviar al servidor. Client guarda el client protocol
 * y el socket*/

#include <string>
#include <memory>

class ClientProtocol {
private:
    bool readResponse;
public:
    ClientProtocol() : readResponse(false) {};
    static std::unique_ptr<char[]> translateCommand(std::string&& command,
                                                    unsigned int& bufferSize); /*recibe el string y lo adapta al protocolo*/
    bool finishedReceiving() const;
    std::unique_ptr<char[]> responseBuffer(unsigned int& bufferLength);
private:
    static std::unique_ptr<char[]> _helpCommand(unsigned int& bufferSize);
    static std::unique_ptr<char[]> _surrenderCommand(unsigned int& bufferSize);
    static std::unique_ptr<char[]> _numberCommand(std::string&& command, unsigned int& bufferSize);
};


#endif //TP3TALLER_CLIENTPROTOCOL_H
