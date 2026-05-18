#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include "personaje.h"
using namespace std;
using namespace sf;

personaje::personaje(Grilla *g)
      {
        grilla = g;
        ladoCelda = g->getTamCeldaPixeles();
        if (!textura.loadFromFile("imagen/character-spritesheet.png")) {
            std::cerr << "Error al cargar textura\n";

        }
        // Construir el sprite con la textura
        sprite = std::make_unique<sf::Sprite>(textura);
     sprite->setPosition(sf::Vector2f(static_cast<float>(0),
                                 static_cast<float>(0)));


    // left, top, width, height


    sprite->setTextureRect(sf::IntRect(
        sf::Vector2i(ladoCelda*0, ladoCelda*0),      // posición inicial dentro del spritesheet
        sf::Vector2i(ladoCelda, ladoCelda)      // tamaño del recorte
    ));

    }

void personaje::cambiarsprt(int nuevox,int nuevoy){

    // left, top, width, height
    //imagen 13X54
    sprite->setTextureRect(sf::IntRect(
        sf::Vector2i(ladoCelda+nuevox, ladoCelda*nuevoy),      // posición inicial dentro del spritesheet
        sf::Vector2i(ladoCelda, ladoCelda)      // tamaño del recorte
    ));

}

void personaje::moverpers(){

if((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)&&(!blokaccion))||((blokaccion)&&(direccion==2)))
{
  if(accion!=1)
  {
    frame=0;
  }
  blokaccion=true;
  posx+=1;
  sprite->setPosition(sf::Vector2f(static_cast<float>(posx),
                                  static_cast<float>(posy)));
     // left, top, width, height
  int x=1;
  int y=11;
  sprite->setTextureRect
  (
    sf::IntRect
    (
      sf::Vector2i(ladoCelda* (x + (frame/8) % 9), ladoCelda*y),      // posición inicial dentro del spritesheet
      sf::Vector2i(ladoCelda, ladoCelda)      // tamaño del recorte
    )
  );
  frame++;
  direccion=2;
  if(frame>=ladoCelda)
  {
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
  sprite->setTextureRect
  (
    sf::IntRect
    (
      sf::Vector2i(ladoCelda* (x + (frame/8) % 9), ladoCelda*y),      // posición inicial dentro del spritesheet
      sf::Vector2i(ladoCelda, ladoCelda)      // tamaño del recorte
    )
  );
    frame++;
    direccion=3;
    if(frame>=ladoCelda){
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
  sprite->setTextureRect
  (
    sf::IntRect
    (
      sf::Vector2i(ladoCelda* (x + (frame/8) % 9), ladoCelda*y),      // posición inicial dentro del spritesheet
      sf::Vector2i(ladoCelda, ladoCelda)      // tamaño del recorte
    )
  );
        frame++;
    direccion=1;
    if(frame>=ladoCelda){
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
  sprite->setTextureRect
  (
    sf::IntRect
    (
      sf::Vector2i(ladoCelda * (x + (frame/8) % 9), ladoCelda*y),      // posición inicial dentro del spritesheet
      sf::Vector2i(ladoCelda, ladoCelda)      // tamaño del recorte
    )
  );
        frame++;
    direccion=4;
    if(frame>=ladoCelda){
    blokaccion=false;
    accion=0;
    frame=0;}
  }
  if(accion=0){
    frame++;
  }
  accion=1;
}
