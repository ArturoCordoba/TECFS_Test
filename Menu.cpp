//
// Created by adrian on 19/11/17.
//

#include "Menu.h"

Menu::Menu(float width, float height)
{

    this->width = width;
    this->height = height;

    if (!font.loadFromFile("CCR.ttf"))
    {
        // handle error
    }

    this->typeOfWindow = 0;

}

Menu::~Menu()
{

}

void Menu::draw(sf::RenderWindow &window)
{

    for(int i = 0; i < NumberOfItems; i++)
    {
        window.draw(menu[i]);
    }
}

void Menu::MoveUp()
{
    if(typeOfWindow == 0) {

        if (selectedItemIndex - 1 >= 0) {
            menu[selectedItemIndex].setColor(sf::Color::White);
            selectedItemIndex--;
            menu[selectedItemIndex].setColor(sf::Color::Red);
        }
    }

    if(typeOfWindow == 1){

        if (selectedItemIndex - 1 >= 0 && selectedItemIndex != 1) {
            menu[selectedItemIndex].setColor(sf::Color::White);
            selectedItemIndex--;
            menu[selectedItemIndex].setColor(sf::Color::Red);
        }
        if (selectedItemIndex == 1){
            menu[selectedItemIndex].setColor(sf::Color::White);
            selectedItemIndex = 0;
            menu[selectedItemIndex].setColor(sf::Color::Red);
        }
    } else if(typeOfWindow == 2){

        if (selectedItemIndex == 10) {
            menu[selectedItemIndex].setColor(sf::Color::White);
            selectedItemIndex = 0;
            menu[selectedItemIndex].setColor(sf::Color::Red);
        }
    }
}

void Menu::MoveDown()
{
    if(typeOfWindow == 0) {

        if (selectedItemIndex + 1 < 3) {
            menu[selectedItemIndex].setColor(sf::Color::White);
            selectedItemIndex++;
            menu[selectedItemIndex].setColor(sf::Color::Red);
        }
    }

    if(typeOfWindow == 1){
        if (selectedItemIndex + 1 < 11 && selectedItemIndex != 0) {
            menu[selectedItemIndex].setColor(sf::Color::White);
            selectedItemIndex++;
            menu[selectedItemIndex].setColor(sf::Color::Red);
        }

        if (selectedItemIndex == 0){
            menu[selectedItemIndex].setColor(sf::Color::White);
            selectedItemIndex = 2;
            menu[selectedItemIndex].setColor(sf::Color::Red);
        }

    } else if(typeOfWindow == 2){

        if (selectedItemIndex == 0) {
            menu[selectedItemIndex].setColor(sf::Color::White);
            selectedItemIndex = 10;
            menu[selectedItemIndex].setColor(sf::Color::Red);
        }
    }
}

void Menu::itemsMenu()
{
    clearItems();
    menu[0].setFont(font);
    menu[0].setColor(sf::Color::Red);
    menu[0].setString("ceSearch");
    menu[0].setPosition(sf::Vector2f(width/3, height /(5) * 1));
    menu[0].setScale(1.5,1.5);

    menu[1].setFont(font);
    menu[1].setColor(sf::Color::White);
    menu[1].setString("ceRobot");
    menu[1].setPosition(sf::Vector2f(width/3, height /(5) * 2));
    menu[1].setScale(1.5,1.5);

    selectedItemIndex = 0;

}

void Menu::itemsSearch()
{
    clearItems();
    menu[0].setFont(font);
    menu[0].setColor(sf::Color::Red);
    menu[0].setString("Buscar Video");
    menu[0].setPosition(sf::Vector2f(width/15, height /(14) * 1));
    menu[0].setScale(1,1);

    menu[1].setFont(font);
    menu[1].setColor(sf::Color::White);
    menu[1].setString("Escriba el nombre del video");
    menu[1].setPosition(sf::Vector2f(width/15, height /(14) * 2));
    menu[1].setScale(1,1);

    menu[10].setFont(font);
    menu[10].setColor(sf::Color::White);
    menu[10].setString("Atras");
    menu[10].setPosition(sf::Vector2f(width/15, height /(14) * 11));
    menu[10].setScale(1,1);

    selectedItemIndex = 0;
}

void Menu::itemsSave()
{
    clearItems();
    menu[0].setFont(font);
    menu[0].setColor(sf::Color::Red);
    menu[0].setString("Guardar Video");
    menu[0].setPosition(sf::Vector2f(width/15, height /(14) * 1));
    menu[0].setScale(1,1);

    menu[1].setFont(font);
    menu[1].setColor(sf::Color::White);
    menu[1].setString("Escribe el path con la extencion del video (.mp4, .mpge)");
    menu[1].setPosition(sf::Vector2f(width/15, height /(14) * 2));
    menu[1].setScale(0.5,1);

    menu[10].setFont(font);
    menu[10].setColor(sf::Color::White);
    menu[10].setString("Atras");
    menu[10].setPosition(sf::Vector2f(width/15, height /(14) * 11));
    menu[10].setScale(0.5,1);

    selectedItemIndex = 0;
}

void Menu::itemsSaveDirectory()
{
    clearItems();
    menu[0].setFont(font);
    menu[0].setColor(sf::Color::Red);
    menu[0].setString("Guardar conjunto de videos");
    menu[0].setPosition(sf::Vector2f(width/15, height /(14) * 1));
    menu[0].setScale(1,1);

    menu[1].setFont(font);
    menu[1].setColor(sf::Color::White);
    menu[1].setString("Escribe el path del directorio");
    menu[1].setPosition(sf::Vector2f(width/15, height /(14) * 2));
    menu[1].setScale(0.5,1);

    menu[10].setFont(font);
    menu[10].setColor(sf::Color::White);
    menu[10].setString("Atras");
    menu[10].setPosition(sf::Vector2f(width/15, height /(14) * 11));
    menu[10].setScale(0.5,1);

    selectedItemIndex = 0;
}

void Menu::setDisplay(std::string inputText)
{
    if(typeOfWindow == 2){
        menu[2].setString("");
    }

    menu[1].setString(inputText);
    display = inputText;
}

void Menu::clearItems()
{
    for (int i = 0; i < NumberOfItems ; ++i) {
        menu[i].setString("");
    }
    this->display = "";
}

void Menu::getTable()
{
    sf::Packet packet;
    packet << "getTable";
    Singleton::getServer()->send(packet);

    //Se espera a recibir la respuesta del servidor
    sf::Packet receivePacket;
    std::string receiveMessage;
    if (Singleton::getServer()->receive(receivePacket) == sf::Socket::Done) {
        receivePacket >> receiveMessage;
    }

    LinkedList<std::string> elements = Singleton::splitString(receiveMessage, "/");
    LinkedList<std::string> names = LinkedList<std::string>();

    for (int i = 1; i < elements.getSize(); ++i) {
        std::string name = Singleton::splitString(elements.getElement(i)->getData(), ";").getElement(0)->getData();
        names.insertAtEnd(name);
    }

    this->names = names;
}

void Menu::search()
{
    getTable();
    if(this->names.getSize() != 0)
    {
        LinkedList<std::string> cNames = coincidence();
        int size = cNames.getSize();
        if(size > 0) {
            for (int i = 0; i < size; ++i) {
                if (i < 8) {

                    int j = i + 2;
                    menu[j].setFont(font);
                    menu[j].setColor(sf::Color::White);
                    menu[j].setString(cNames.getElement(i)->getData());
                    menu[j].setPosition(sf::Vector2f(width/15, height/(11) * (i + 3)));
                    menu[j].setScale(0.5, 0.5);
                }
            }
            if (size < 8) {
                for (int i = 0; i < (8 - size); ++i) {

                    int j = size + i + 2;
                    menu[j].setFont(font);
                    menu[j].setColor(sf::Color::White);
                    menu[j].setString(" ");
                    menu[j].setPosition(sf::Vector2f(width / 15, height / (11) * (size + i + 3)));
                    menu[j].setScale(0.5, 0.5);
                }
            }
            this->typeOfWindow = 1;

        }else{
            menu[2].setFont(font);
            menu[2].setColor(sf::Color::White);
            menu[2].setString("No se encontro videos");
            menu[2].setPosition(sf::Vector2f(width/15, height /(14) * 3));
            menu[2].setScale(1,1);

            for (int i = 3; i < 10 ; ++i) {
                menu[i].setString("");
            }
        }
    }else{
        menu[2].setFont(font);
        menu[2].setColor(sf::Color::White);
        menu[2].setString("No se encontro videos");
        menu[2].setPosition(sf::Vector2f(width/15, height /(14) * 3));
        menu[2].setScale(1,1);

        for (int i = 3; i < 10 ; ++i) {
            menu[i].setString("");
        }
    }
}

void Menu::playVideo(int i)
{
    if(menu[i].getString() != " ") {
        std::string video = VideoHandler::getVideo(menu[i].getString());
        VideoPlayerWindow::render("receive.mp4");
    }
}

LinkedList<std::string> Menu::coincidence()
{

    LinkedList<std::string> coinNames;
    int size = this->display.length();

        for (int i = 0; i < this->names.getSize(); ++i) {
            if(size <= this->names.getElement(i)->getData().length()) {
                std::string subString = this->names.getElement(i)->getData().substr(0, (size));
                int bd = strncmp(display.c_str(), subString.c_str(), size);
                if (bd == 0) {
                    coinNames.insertAtFirst(this->names.getElement(i)->getData());
                }
            }
        }


    return coinNames;
}

void Menu::saveVideo()
{
    if (VideoHandler::sendVideo(display) == 0)
    {
        menu[2].setFont(font);
        menu[2].setColor(sf::Color::White);
        menu[2].setString("El video se guardo con exito");
        menu[2].setPosition(sf::Vector2f(width/15, height /(14) * 3));
        menu[2].setScale(1,1);
    } else{
        menu[2].setFont(font);
        menu[2].setColor(sf::Color::White);
        menu[2].setString("No se encontro el video");
        menu[2].setPosition(sf::Vector2f(width/15, height /(14) * 3));
        menu[2].setScale(1,1);
    }
}

void Menu::itemsMenuSave() {
    clearItems();
    menu[0].setFont(font);
    menu[0].setColor(sf::Color::Red);
    menu[0].setString("Guardar video");
    menu[0].setPosition(sf::Vector2f(width/5, height /(5) * 1));
    menu[0].setScale(1.5,1.5);

    menu[1].setFont(font);
    menu[1].setColor(sf::Color::White);
    menu[1].setString("Guardar carpeta");
    menu[1].setPosition(sf::Vector2f(width/5, height /(5) * 2));
    menu[1].setScale(1.5,1.5);

    menu[2].setFont(font);
    menu[2].setColor(sf::Color::White);
    menu[2].setString("Atras");
    menu[2].setPosition(sf::Vector2f(width/5, height /(5) * 4));
    menu[2].setScale(1.5,1.5);

    selectedItemIndex = 0;


}

void Menu::saveDirectory()
{
    if (VideoHandler::sendDirectory(display) == 0)
    {
        menu[2].setFont(font);
        menu[2].setColor(sf::Color::White);
        menu[2].setString("El conjunto de videos \n se guardo con exito");
        menu[2].setPosition(sf::Vector2f(width/15, height /(14) * 3));
        menu[2].setScale(1,1);
    } else{
        menu[2].setFont(font);
        menu[2].setColor(sf::Color::White);
        menu[2].setString("No se encontro el directorio");
        menu[2].setPosition(sf::Vector2f(width/15, height /(14) * 3));
        menu[2].setScale(1,1);
    }
}

void Menu::run() {
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
                                        numberOfWindow = 3;
                                        menu.itemsMenuSave();
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
                                        window.close();
                                        menu.playVideo(menu.GetPressdItem());
                                        break;
                                    case 10:
                                        numberOfWindow = 0;
                                        menu.itemsMenu();
                                        menu.typeOfWindow = 0;
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
                        window.close();
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

                                    case 10:
                                        numberOfWindow = 3;
                                        menu.itemsMenuSave();
                                        menu.typeOfWindow = 0;
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
                        window.close();
                        break;
                }
            }
        } else if (numberOfWindow == 3) {
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
                                        numberOfWindow = 2;
                                        menu.itemsSave();
                                        menu.typeOfWindow = 2;
                                        display = "";
                                        break;

                                    case 1:
                                        numberOfWindow = 4;
                                        menu.itemsSaveDirectory();
                                        menu.typeOfWindow = 2;
                                        display = "";
                                        break;

                                    case 2:
                                        numberOfWindow = 0;
                                        menu.itemsMenu();
                                        menu.typeOfWindow = 0;
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

        } else if (numberOfWindow == 4) {
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
                                        menu.saveDirectory();
                                        break;

                                    case 10:
                                        numberOfWindow = 3;
                                        menu.itemsMenuSave();
                                        menu.typeOfWindow = 0;
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
                        window.close();
                        break;
                }
            }
        }

        window.clear();
        window.draw(bgS);
        menu.draw(window);
        window.display();
    }
}


