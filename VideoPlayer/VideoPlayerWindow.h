//
// Created by arturocv on 26/11/17.
//

#ifndef TECFS_TEST_VIDEOPLAYERWINDOW_H
#define TECFS_TEST_VIDEOPLAYERWINDOW_H

#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>
#include <sfeMovie/Movie.hpp>
#include <iostream>
#include "UserInterface.hpp"
#include "StreamSelector.hpp"

class VideoPlayerWindow {
public:
    static int render(std::string fileName);
};


#endif //UNTITLED_VIDEOPLAYERWINDOW_H
