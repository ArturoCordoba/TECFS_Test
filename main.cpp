#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>

using namespace std;

const sf::IpAddress IP = "10.0.2.15";
const int PORT = 2000;

int main(int argc, char const *argv[])
{
    string id;
    cout << "Nombre de Usuario: " << endl;
    cin >> id;

    sf::TcpSocket socket;
    socket.connect(IP,PORT);

    sf::Packet packet;
    packet << id;
    socket.send(packet);
    return 0;
}