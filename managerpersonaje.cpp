#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include "managerpersonaje.h"




using namespace std;
using namespace sf;


void managerpersonaje::moverpersonaje(personaje& pers){


if((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)&&(!pers.getblockaccion()))||((pers.getblockaccion())&&(pers.getdireccion()==2)))
{
  if(pers.getaccion()!=1)
  {
    pers.setframe(0);
  }
  pers.setblockaccion(true);
  pers.setsumresposx(1);
 // posx+=1;
 // sprite.setPosition(sf::Vector2f(pers.getposx(),pers.getposy()));
  pers.setposicionsprite(pers.getposx(),pers.getposy());
     // left, top, width, height
  int x=1;
  int y=11;
  pers.setsubrectsprite(pers.getladocelda()* (x + (pers.getframe()/8) % 9), pers.getladocelda()*y,pers.getladocelda(), pers.getladocelda() );
 // sprite.setTextureRect
 // (
 //   sf::IntRect
 //   (
 //     sf::Vector2i(ladoCelda* (x + (frame/8) % 9), ladoCelda*y),      // posición inicial dentro del spritesheet
 //     sf::Vector2i(ladoCelda, ladoCelda)      // tamaño del recorte
 //   )
 // );
  pers.sumarframe();
  //frame++;
  pers.setdireccion(2);
  //direccion=2;
  if(pers.getframe()>=pers.getladocelda())
  {
    pers.setblockaccion(false);
    pers.setaccion(0);
   // accion=0;
    pers.setframe(0);
   // frame=0;
  }
}
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)&&(!pers.getblockaccion())||(pers.getblockaccion())&&(pers.getdireccion()==3)){
if(pers.getaccion()!=1){
pers.setframe(0);
    }
pers.setaccion(1);
                pers.setblockaccion(true);
    pers.setsumresposx(-1);
  pers.setposicionsprite(pers.getposx(),pers.getposy());
       int x=1;
       int y=9;
pers.setsubrectsprite(pers.getladocelda()* (x + (pers.getframe()/8) % 9), pers.getladocelda()*y,pers.getladocelda(), pers.getladocelda() );
    pers.sumarframe();
    pers.setdireccion(3);
   // direccion=3;
      if(pers.getframe()>=pers.getladocelda())
  {
   pers.setblockaccion(false);
    pers.setaccion(0);
    pers.setframe(0);}
  }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)&&(!pers.getblockaccion())||(pers.getblockaccion())&&(pers.getdireccion()==1)){
if(pers.getaccion()!=1){
pers.setframe(0);
    }
pers.setaccion(1);
                pers.setblockaccion(true);
   pers.setsumresposy(-1);
   //posy-=1;
   pers.setposicionsprite(pers.getposx(),pers.getposy());
       int x=1;
       int y=8;
pers.setsubrectsprite(pers.getladocelda()* (x + (pers.getframe()/8) % 9), pers.getladocelda()*y,pers.getladocelda(), pers.getladocelda() );
        pers.sumarframe();
    pers.setdireccion(1);
   // direccion=1;
  if(pers.getframe()>=pers.getladocelda())
  {
    pers.setblockaccion(false);
    pers.setaccion(0);
    pers.setframe(0);}
  }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)&&(!pers.getblockaccion())||(pers.getblockaccion())&&(pers.getdireccion()==4)){
    if(pers.getaccion()!=1){
pers.setframe(0);
    }
pers.setaccion(1);
                pers.setblockaccion(true);
    pers.setsumresposy(1);
   // posy+=1;
    pers.setposicionsprite(pers.getposx(),pers.getposy());
       int x=1;
       int y=10;
pers.setsubrectsprite(pers.getladocelda()* (x + (pers.getframe()/8) % 9), pers.getladocelda()*y,pers.getladocelda(), pers.getladocelda() );
        pers.sumarframe();
    pers.setdireccion(4);
   // direccion=4;
  if(pers.getframe()>=pers.getladocelda())
  {
    pers.setblockaccion(false);
    pers.setaccion(0);
    pers.setframe(0);}
  }
  if(pers.getaccion()==0){
    pers.sumarframe();
  }
  pers.setaccion(1);
}



void managerpersonaje::mostrarpersonaje(personaje pers,sf::RenderWindow& window) {
        window.draw(pers.getsprite());
    }
