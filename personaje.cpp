#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include <string>
#include "personaje.h"
using namespace std;
using namespace sf;


void personaje::cambiarsprt(int nuevox,int nuevoy){

    // left, top, width, height
    //imagen 13X54
    sprite->setTextureRect(sf::IntRect(
        sf::Vector2i(64+nuevox, 64*nuevoy),      // posición inicial dentro del spritesheet
        sf::Vector2i(64, 64)      // tamaño del recorte
    ));

}

void personaje::moverpers(){

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)&&(!blokaccion)||(blokaccion)&&(direccion==2)){
if(accion!=1){
frame=0;
    }
    blokaccion=true;
    posx+=1;
    sprite->setPosition(sf::Vector2f(static_cast<float>(posx),
                                    static_cast<float>(posy)));
       // left, top, width, height
       int x=1;
       int y=11;
    sprite->setTextureRect(sf::IntRect(
        sf::Vector2i(64/x, 64*y),      // posición inicial dentro del spritesheet
        sf::Vector2i(64, 64)      // tamaño del recorte
    ));
    frame++;
    direccion=2;
    if(frame>=64){
    blokaccion=false;
    accion=0;
    frame=0;
    }

  }
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)&&(!blokaccion)||(blokaccion)&&(direccion==3)){
if(accion!=1){
frame=0;
    }
accion=1;
                blokaccion=true;
    posx-=1;
    sprite->setPosition(sf::Vector2f(static_cast<float>(posx),
                                    static_cast<float>(posy)));
       int x=1;
       int y=9;
       sprite->setTextureRect(sf::IntRect(
        sf::Vector2i(64/x, 64*y),      // posición inicial dentro del spritesheet
        sf::Vector2i(64, 64)      // tamaño del recorte
    ));
    frame++;
    direccion=3;
    if(frame>=64){
    blokaccion=false;
    accion=0;
    frame=0;}
  }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)&&(!blokaccion)||(blokaccion)&&(direccion==1)){
if(accion!=1){
frame=0;
    }
accion=1;
                blokaccion=true;
   posy-=1;
    sprite->setPosition(sf::Vector2f(static_cast<float>(posx),
                                    static_cast<float>(posy)));
       int x=1;
       int y=8;
    sprite->setTextureRect(sf::IntRect(
        sf::Vector2i(64/x, 64*y),      // posición inicial dentro del spritesheet
        sf::Vector2i(64, 64)      // tamaño del recorte
    ));
        frame++;
    direccion=1;
    if(frame>=64){
    blokaccion=false;
    accion=0;
    frame=0;}
  }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)&&(!blokaccion)||(blokaccion)&&(direccion==4)){
    if(accion!=1){
frame=0;
    }
accion=1;
                blokaccion=true;
    posy+=1;
    sprite->setPosition(sf::Vector2f(static_cast<float>(posx),
                                    static_cast<float>(posy)));
       int x=1;
       int y=10;
    sprite->setTextureRect(sf::IntRect(
        sf::Vector2i(64/x, 64*y),      // posición inicial dentro del spritesheet
        sf::Vector2i(64, 64)      // tamaño del recorte
    ));
        frame++;
    direccion=4;
    if(frame>=64){
    blokaccion=false;
    accion=0;
    frame=0;}
  }
  if(accion=0){
    frame++;
  }
  accion=1;
}


