#include <iostream>
#include <cstring>
#include "VideoHandler.h"
#include "DataStructures/LinkedList.h"

LinkedList<std::string> splitString(std::string string, char *splitCharacter);

int main(){
    Singleton::connectToServer("127.0.0.1", 2001);

    while(true) {
        int action;
        std::string filename;
        std::cout << "Ingrese el numero de la accion a realizar: " << std::endl;
        std::cout << "1. Enviar video" << std::endl;
        std::cout << "2. Recibir video" << std::endl;
        std::cout << "3. Obtener tabla" << std::endl;
        std::cin >> action;

        if (action == 1) {
            std::cout << "Ingrese el nombre del video (con extension): " << std::endl;
            std::cin >> filename;
            VideoHandler::sendVideo(filename);

        } else if (action == 2) {
            std::cout << "Ingrese el nombre del video (sin extension): " << std::endl;
            std::cin >> filename;
            VideoHandler::getVideo(filename);

            VideoHandler::getVideo("test");
        } else if(action == 3){
            sf::Packet packet;
            packet << "getTable";
            Singleton::getServer()->send(packet);

            //Se espera a recibir la respuesta del servidor
            sf::Packet receivePacket;
            std::string receiveMessage;
            if (Singleton::getServer()->receive(receivePacket) == sf::Socket::Done) {
                receivePacket >> receiveMessage;
            }

            std::string table = "";
            LinkedList<std::string> rows = splitString(receiveMessage.c_str(), "/");
            for (int i = 0; i < rows.getSize(); ++i) {
                table += rows.getElement(i)->getData() + "\n";
            }

            std::vector<byte> vector(table.begin(), table.end());
            std::ofstream file;
            file.open("data.csv", std::ios::out | std::ios::binary);
            file.write((const char*) &vector[0], vector.size());
            file.close();
        }

        action = 0;
        filename = "";
    }

    return 0;
}

/// Metodo para dividir un string en elementos
/// \param string String a separar
/// \param splitCharacter Caracter utilizado para separar los elementos
/// \return LinkedList con los elementos obtenidos de la separacion
LinkedList<std::string> splitString(std::string string, char *splitCharacter) {
    LinkedList<std::string> list = LinkedList<std::string>(); //Lista en la que se guardan los elementos
    char* messageChar = strdup(string.c_str()); //Se transforma el mensaje a char*
    char* element = strtok(messageChar, splitCharacter); //Separa el char cuando lea el splitCharacter
    while (element != NULL) {
        std::string str(element);
        list.insertAtEnd(str); // Se guarda el dato en la lista
        element = strtok (NULL, splitCharacter);  // Separa el resto de la cadena cuando lea la coma
    }

    return list;
}
