//
// Created by arturocv on 14/11/17.
//

#include <SFML/Network/Packet.hpp>
#include "Singleton.h"

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
    server->connect(sf::IpAddress(ip), port);
    sf::Packet packet;
    packet << "client";
    server->send(packet);
}

sf::TcpSocket *Singleton::getServer() {
    if(instance == nullptr){
        getInstance();
    }

    return server;
}
