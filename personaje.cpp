#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include <string>
#include "personaje.h"
using namespace std;
using namespace sf;


void personaje::cambiarsprt(int nuevox,int nuevoy){

    // left, top, width, height
    sprite->setTextureRect(sf::IntRect(
        sf::Vector2i(64+nuevox, 64*nuevoy),      // posición inicial dentro del spritesheet
        sf::Vector2i(64, 64)      // tamaño del recorte
    ));

}

void personaje::moverpers(){

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){
    posx+=10;
    sprite->setPosition(sf::Vector2f(static_cast<float>(posx),
                                    static_cast<float>(posy)));
       // left, top, width, height
       int x=1;
       int y=1;
    sprite->setTextureRect(sf::IntRect(
        sf::Vector2i(64/x, 64*y),      // posición inicial dentro del spritesheet
        sf::Vector2i(64, 64)      // tamaño del recorte
    ));


  }
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)){
    posx-=10;
    sprite->setPosition(sf::Vector2f(static_cast<float>(posx),
                                    static_cast<float>(posy)));

  }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){
   posy-=10;
    sprite->setPosition(sf::Vector2f(static_cast<float>(posx),
                                    static_cast<float>(posy)));

  }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)){
    posy+=10;
    sprite->setPosition(sf::Vector2f(static_cast<float>(posx),
                                    static_cast<float>(posy)));

  }
}


