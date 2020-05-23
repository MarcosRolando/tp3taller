#ifndef TP3TALLER_CLIENTPROTOCOL_H
#define TP3TALLER_CLIENTPROTOCOL_H

/*Esta clase se encarga de pasar los comandos ingresados por el usuario al
 * protocolo correspondiente para ser enviado al Server*/

#include <string>
#include <memory>

class ClientProtocol {
private:
    bool readLength, readResponse, finished;
    uint32_t responseLength;

public:
    ClientProtocol() : readLength(false), readResponse(false), finished(false),
                                                        responseLength(0) {}

    /*Recibe el comando del ususario y lo traduce acorde al protocolo*/
    static std::unique_ptr<char[]> translateCommand(std::string&& command,
                                                    unsigned int& bufferSize);

    /*Retorna si termino de recibir la respuesta del servidor*/
    bool finishedReceiving() const;

    /*Retorna el buffer a llenar por el mensaje junto con su longitud*/
    std::unique_ptr<char[]> responseBuffer(unsigned int& bufferLength);

    /*Procesa la respuesta recibida por el servidor*/
    void processResponse(std::unique_ptr<char[]>& response);

    /*Retorna si se termino la comunicacion con el servidor, es decir, cuando
     * se termina el juego*/
    bool hasFinished() const;

private:
    static std::unique_ptr<char[]> _helpCommand(unsigned int& bufferSize);
    static std::unique_ptr<char[]> _surrenderCommand(unsigned int& bufferSize);
    static std::unique_ptr<char[]> _numberCommand(std::string&& command,
                                                    unsigned int& bufferSize);
};

#endif //TP3TALLER_CLIENTPROTOCOL_H
