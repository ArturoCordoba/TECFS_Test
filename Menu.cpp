//
// Created by adrian on 19/11/17.
//

#include <cstring>
#include "Menu.h"
#include "Singleton.h"
#include "VideoHandler.h"

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
    }
}

void Menu::MoveDown()
{
    if(typeOfWindow == 0) {

        if (selectedItemIndex + 1 < 2) {
            menu[selectedItemIndex].setColor(sf::Color::White);
            selectedItemIndex++;
            menu[selectedItemIndex].setColor(sf::Color::Red);
        }
    }

    if(typeOfWindow == 1){
        if (selectedItemIndex + 1 < 10 && selectedItemIndex != 0) {
            menu[selectedItemIndex].setColor(sf::Color::White);
            selectedItemIndex++;
            menu[selectedItemIndex].setColor(sf::Color::Red);
        }

        if (selectedItemIndex == 0){
            menu[selectedItemIndex].setColor(sf::Color::White);
            selectedItemIndex = 2;
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
    selectedItemIndex = 0;
}

void Menu::setDisplay(std::string inputText)
{
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

    LinkedList<std::string> elements = splitString(receiveMessage, "/");
    LinkedList<std::string> names = LinkedList<std::string>();

    for (int i = 1; i < elements.getSize(); ++i) {
        std::string name = splitString(elements.getElement(i)->getData(), ";").getElement(0)->getData();
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
        cv::VideoCapture cap("receive.mp4");

        if (!cap.isOpened()) {
            std::cout << "Cannot open the video file. \n";
        }
        double fps = cap.get(CV_CAP_PROP_FPS);
        cv::namedWindow("Reproductor", CV_WINDOW_AUTOSIZE);
        while (1) {
            cv::Mat frame;
            if (!cap.read(frame)) {
                std::cout << "\n Cannot read the video file. \n";
                break;
            }
            imshow("Reproductor", frame);

            if(cv::waitKey(30) >= 0) {
                break;
            }
        }
    }
}

/// Metodo para dividir un string en elementos
/// \param string String a separar
/// \param splitCharacter Caracter utilizado para separar los elementos
/// \return LinkedList con los elementos obtenidos de la separacion
LinkedList<std::string> Menu::splitString(std::string string, char *splitCharacter) {
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



