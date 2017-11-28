#include <iostream>
#include <SFML/Graphics.hpp>
#include "VideoHandler.h"
#include "Menu.h"


int main() {
    std::string ip;
    std::cout << "Ingrese la IP del servidor: ";
    std::cin >> ip;

    Singleton::connectToServer(ip, 2001);

    Menu::run();

    return 0;
}
