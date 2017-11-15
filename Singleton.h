//
// Created by arturocv on 14/11/17.
//

#ifndef TECFS_TEST_SINGLETON_H
#define TECFS_TEST_SINGLETON_H


#include <iostream>
#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Network/IpAddress.hpp>

class Singleton {
public:
    static Singleton* getInstance();

    static void connectToServer(std::string ip, int port);

    static sf::TcpSocket* getServer();

private:
    static Singleton* instance;

    static sf::TcpSocket* server;
};


#endif //TECFS_TEST_SINGLETON_H
