//
// Created by arturocv on 14/11/17.
//

#include <SFML/Network/Packet.hpp>
#include <cstring>
#include "Singleton.h"
#include "DataStructures/LinkedList.h"

Singleton* Singleton::instance = nullptr;
sf::TcpSocket* Singleton::server = nullptr;

Singleton *Singleton::getInstance() {
    //Se crean las instancias si estas no existian previamente
    if(instance == nullptr){
        instance = new Singleton();
        server = new sf::TcpSocket();
    }

    return instance;
}

/// Metodo para conertarse al servidor
/// \param ip IP del servidor
/// \param port Puerto del servidor
void Singleton::connectToServer(std::string ip, int port) {
    if(instance == nullptr){
        getInstance();
    }

    //Se conecta al servidor y le indica que se trata de un cliente
    if(server->connect(sf::IpAddress(ip), port) == sf::Socket::Done){
        sf::Packet packet;
        packet << "client";
        server->send(packet);
    } else{
        std::cout << "Couldn't connect to the server" << std::endl;
    }
}

sf::TcpSocket *Singleton::getServer() {
    if(instance == nullptr){
        getInstance();
    }

    return server;
}

/// Metodo para dividir un string en elementos
/// \param string String a separar
/// \param splitCharacter Caracter utilizado para separar los elementos
/// \return LinkedList con los elementos obtenidos de la separacion
LinkedList<std::string> Singleton::splitString(std::string string, char *splitCharacter) {
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