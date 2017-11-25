//
// Created by arturocv on 14/11/17.
//

#ifndef TECFS_TEST_VIDEOHANDLER_H
#define TECFS_TEST_VIDEOHANDLER_H

#include <iostream>
#include <SFML/Network/Packet.hpp>
#include <SFML/Network/Socket.hpp>
#include <fstream>
#include "Singleton.h"

typedef unsigned char byte;

class VideoHandler {
public:
    static int sendVideo(std::string pathFile);

    static std::string getVideo(std::string fileName);
};


#endif //TECFS_TEST_VIDEOHANDLER_H
