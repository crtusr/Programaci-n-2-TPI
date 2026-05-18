#ifndef PERSONAJE_H_INCLUDED
#define PERSONAJE_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include <string>
#include <memory>
using namespace std;
using namespace sf;


class personaje {
private:
    int posx = 0;
    int posy = 0;
    int direccion = 0;
    int accion = 0;
    bool blokaccion = false;
    int frame = 0;

    sf::Texture textura;
    std::unique_ptr<sf::Sprite> sprite;

public:
    // Constructor
    personaje()
      {
        if (!textura.loadFromFile("imagen/character-spritesheet.png")) {
            std::cerr << "Error al cargar textura\n";

        }
        // Construir el sprite con la textura
        sprite = std::make_unique<sf::Sprite>(textura);
     sprite->setPosition(sf::Vector2f(static_cast<float>(0),
                                 static_cast<float>(0)));


    // left, top, width, height


    sprite->setTextureRect(sf::IntRect(
        sf::Vector2i(64*0, 65*0),      // posición inicial dentro del spritesheet
        sf::Vector2i(64, 64)      // tamaño del recorte
    ));

    }

    // Getters
    int getposx() const { return posx; }
    int getposy() const { return posy; }
    int getdireccion() const { return direccion; }
    int getaccion() const { return accion; }



    //---------arreglando---------//

        void mostrarpersonaje(sf::RenderWindow& window) {
        window.draw(*sprite);
    }
//void setposx(int x) {
//    posx = x;
//    sprite->setPosition(sf::Vector2f(static_cast<float>(posx),
//                                    static_cast<float>(posy)));
//}

//void setposy(int y) {
//    posy = y;
//    sprite->setPosition(sf::Vector2f(static_cast<float>(posx),
//                                    static_cast<float>(posy)));
//    }

void cambiarsprt(int nuevox,int nuevoy);
void moverpers();



};
