#include <iostream>
#include "VideoHandler.h"

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

            //sendVideo("test.mp4");
        } else if (action == 2) {
            std::cout << "Ingrese el nombre del video (sin extension): " << std::endl;
            std::cin >> filename;
            VideoHandler::getVideo(filename);

            //getVideo("test");
        } else if(action == 3){
            sf::Packet packet;
            packet << "getTable";
            Singleton::getServer()->send(packet);

            //Se espera a recibir la respuesta del servidor
            sf::Packet receivePacket;
            std::string receiveMessage;
            while(true){
                if (Singleton::getServer()->receive(receivePacket) == sf::Socket::Done) {
                    receivePacket >> receiveMessage;
                    break;
                }
            }

            std::cout << std::endl << receiveMessage << std::endl << std::endl;
        }
    }

    return 0;
}