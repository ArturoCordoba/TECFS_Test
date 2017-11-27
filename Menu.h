//
// Created by adrian on 19/11/17.
//

#ifndef TECFS_TEST_MENU_H
#define TECFS_TEST_MENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Network/Packet.hpp>
#include <dirent.h>
#include <cstring>
#include "DataStructures/LinkedList.h"
#include "Singleton.h"
#include "VideoHandler.h"
#include "VideoPlayer/VideoPlayerWindow.h"


#define NumberOfItems 10

class Menu
{
public:
    Menu(float width, float height);
    ~Menu();

    void draw(sf::RenderWindow &window);
    void MoveUp();
    void MoveDown();
    void itemsMenu();
    void itemsSearch();
    void itemsSave();
    int typeOfWindow;
    int GetPressdItem() {return  selectedItemIndex;}
    void setDisplay(std::string string);
    void search();
    void playVideo(int i);
    std::string display = "";
    void saveVideo();

private:
    float width;
    float height;
    int selectedItemIndex;
    sf::Font font;
    sf::Text menu[NumberOfItems];
    LinkedList<std::string> names;
    void clearItems();
    void getTable();
    LinkedList<std::string> coincidence();
};


#endif //TECFS_TEST_MENU_H
