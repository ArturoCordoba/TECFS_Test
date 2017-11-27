//
// Created by arturocv on 14/11/17.
//

#include "VideoHandler.h"

/// Metodo para enviar un video al servidor
/// \param pathFile Ruta del video
/// \return 0 si se realizo con exito, -1 si hubo un error
int VideoHandler::sendVideo(std::string pathFile) {
    std::ifstream file(pathFile, std::ios::binary);

    //Se verifica que el video haya sido cargado de manera existosa
    if(!file.is_open()){
        std::cout << "Couldn't open the file" << std::endl;
        return -1;

    } else {
        //Se obtiene el nombre del video del path ingresado
        LinkedList<std::string> list = Singleton::splitString(pathFile, "/");
        std::string videoName = list.getElement(list.getSize() -1)->getData();

        //Se le indica al servidor que se quiere almacenar un video
        sf::Packet actionPacket;
        actionPacket << "saveVideo";
        actionPacket << videoName;
        Singleton::getServer()->send(actionPacket);

        //Se convierte el video a un string de <uchar>
        std::vector<byte> vector((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        std::string vectorString(vector.begin(), vector.end());
        file.close();

        //Se envia el video
        sf::Packet videoPacket;
        videoPacket << vectorString;
        Singleton::getServer()->send(videoPacket);

        return 0;
    }
}

/// Metodo para obtener un video del servidor
/// \param fileName Nombre del video que se quiere obtener
std::string VideoHandler::getVideo(std::string fileName){
    //Se envia al servidor la accion que se quiere realizar
    sf::Packet packet;
    packet << "getVideo";
    packet << fileName;
    Singleton::getServer()->send(packet);

    //Se espera a recibir la respuesta del servidor
    sf::Packet receivePacket;
    std::string receiveMessage;

    if (Singleton::getServer()->receive(receivePacket) == sf::Socket::Done) {
        receivePacket >> receiveMessage;
    }


    //Se guarda el video recibido
    std::string extension;
    receivePacket >> extension;

    std::vector<byte> vector(receiveMessage.begin(), receiveMessage.end());
    std::ofstream file;
    file.open("receive." + extension, std::ios::out | std::ios::binary);
    file.write((const char*) &vector[0], vector.size());
    file.close();

    return receiveMessage;
}

/// Metodo para enviar los archivos que se encuentren dentro de una carpeta
/// \param pathDirectory Path de la carpeta
/// \return 0 si no ocurrieron errores, -1 en caso contrario.
int VideoHandler::sendDirectory(std::string pathDirectory) {
    DIR* dir;
    struct dirent *ent;
    //Se intenta abrir el directorio
    if((dir = opendir(pathDirectory.c_str())) != NULL){
        //Se lee cada archivo dentro del directorio
        while((ent = readdir(dir)) != NULL) {
            std::string fileName = ent->d_name;
            //Se verifica que sea un nombre de video valido
            if (fileName.size() > 4 && Singleton::splitString(fileName, ".").getSize() == 2) {
                sendVideo(pathDirectory + "/" + fileName);
            }
        }
        closedir(dir);
        return 0;

    } else{
        return -1;
    }
}
