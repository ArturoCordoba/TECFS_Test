#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <fstream>
#include <iostream>

typedef unsigned char byte;

const sf::IpAddress IP = "127.0.0.1";
const int PORT = 2000;
sf::TcpSocket socket;

int sendVideo(std::string path);

int main(){

    socket.connect(IP, PORT);

    sf::Packet packet;
    packet << "Arturocv";
    socket.send(packet);

    sendVideo("test.mp4");

    return 0;
}

int sendVideo(std::string path) {
    sf::Packet actionPacket;
    actionPacket << "save";
    socket.send(actionPacket);

    sf::Packet videoPacket;
    std::ifstream file(path, std::ios::binary);

    //Se verifica que el video haya sido cargado de manera existosa
    if(!file.is_open()){
        std::cout << "Couldn't open the binary file" << std::endl;
        return -1;
    }

    //Se convierte el video a un string de <uchar>
    std::vector<byte> vector((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    std::string vectorString(vector.begin(), vector.end());
    file.close();

    //Se envia el video
    videoPacket << vectorString;
    socket.send(videoPacket);

    sf::Packet donePacket;
    donePacket << "done";
    socket.send(donePacket);

    return 0;
}