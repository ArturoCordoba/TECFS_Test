#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstring>
#include "VideoHandler.h"
#include "Menu.h"
#include <SFML/OpenGL.hpp>


int main() {

    Singleton::connectToServer("192.168.100.9", 2001);
    int numberOfWindow = 0;
    sf::RenderWindow window;
    window.create(sf::VideoMode(640,480), "TECFS_Test");
    window.setPosition(sf::Vector2i(100,100));

    sf::Texture bg;
    sf::Sprite bgS;
    if(!bg.loadFromFile("bg.jpg"))
        std::cout << "Error could not load nave image" << std::endl;
    bgS.setTexture(bg);
    bgS.setScale(0.5f,0.5f);

    Menu menu(window.getSize().x, window.getSize().y);
    menu.itemsMenu();
    std::string display = "";

    while (window.isOpen()){

        if (numberOfWindow == 0) {
            sf::Event event;
            while (window.pollEvent(event)) {
                switch (event.type) {
                    case sf::Event::KeyReleased:
                        switch (event.key.code) {
                            case sf::Keyboard::Up:
                                menu.MoveUp();
                                break;

                            case sf::Keyboard::Down:
                                menu.MoveDown();
                                break;

                            case sf::Keyboard::Tab:
                                switch (menu.GetPressdItem()) {
                                    case 0:
                                        numberOfWindow = 1;
                                        menu.itemsSearch();
                                        menu.typeOfWindow = 2;
                                        display = "";
                                        break;

                                    case 1:
                                        numberOfWindow = 2;
                                        menu.itemsSave();
                                        menu.typeOfWindow = 2;
                                        display = "";
                                        break;
                                }
                                break;
                        }
                        break;

                    case sf::Event::Closed:
                        window.close();
                        break;
                }
            }

        } if (numberOfWindow == 1) {
            sf::Event event;
            while (window.pollEvent(event)) {
                switch (event.type) {
                    case sf::Event::KeyReleased:
                        switch (event.key.code) {
                            case sf::Keyboard::Up:
                                menu.MoveUp();
                                break;

                            case sf::Keyboard::Down:
                                menu.MoveDown();
                                break;

                            case sf::Keyboard::Tab:
                                switch (menu.GetPressdItem()) {
                                    case 0:
                                        menu.search();
                                        break;

                                    case 2:
                                    case 3:
                                    case 4:
                                    case 5:
                                    case 6:
                                    case 7:
                                    case 8:
                                    case 9:
                                        menu.playVideo(menu.GetPressdItem());
                                        break;
                                }
                        }
                        break;

                    case sf::Event::TextEntered:
                        if (event.text.unicode >= 20 && event.text.unicode <= 126)
                            display += (char) event.text.unicode;
                        else if (event.text.unicode == 8)
                            display = display.substr(0, display.length() - 1);
                        menu.setDisplay(display);
                        break;

                    case sf::Event::Closed:
                        numberOfWindow = 0;
                        menu.itemsMenu();
                        menu.typeOfWindow = 0;
                        break;

                }
            }

        } if (numberOfWindow == 2) {
            sf::Event event;
            while (window.pollEvent(event)) {
                switch (event.type) {
                    case sf::Event::KeyReleased:
                        switch (event.key.code) {
                            case sf::Keyboard::Up:
                                menu.MoveUp();
                                break;

                            case sf::Keyboard::Down:
                                menu.MoveDown();
                                break;

                            case sf::Keyboard::Tab:
                                switch (menu.GetPressdItem()) {
                                    case 0:
                                        menu.saveVideo();
                                        break;
                                }
                        }
                        break;

                    case sf::Event::TextEntered:
                        if (event.text.unicode >= 20 && event.text.unicode <= 126)
                            display += (char) event.text.unicode;
                        else if (event.text.unicode == 8)
                            display = display.substr(0, display.length() - 1);
                        menu.setDisplay(display);
                        break;

                    case sf::Event::Closed:
                        numberOfWindow = 0;
                        menu.itemsMenu();
                        menu.typeOfWindow = 0;
                        break;
                }
            }
        }

        window.clear();
        window.draw(bgS);
        menu.draw(window);
        window.display();
    }

    return 0;
}
