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
  pers.setposicionsprite(pers.getPosicionF());
  int x=1;
  int y=11;
  pers.setsubrectsprite(pers.getladocelda()* (x + (pers.getframe()/8) % 9), pers.getladocelda()*y,pers.getladocelda(), pers.getladocelda() );
  pers.sumarframe();
  pers.setdireccion(2);
  if(pers.getframe()>=pers.getladocelda())
  {
    pers.setblockaccion(false);
    pers.setaccion(0);
    pers.setframe(0);
  }
}
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)&&(!pers.getblockaccion())||(pers.getblockaccion())&&(pers.getdireccion()==3)){
if(pers.getaccion()!=1){
pers.setframe(0);
    }
pers.setaccion(1);
                pers.setblockaccion(true);
    pers.setsumresposx(-1);
  pers.setposicionsprite(pers.getPosicionF());
       int x=1;
       int y=9;
pers.setsubrectsprite(pers.getladocelda()* (x + (pers.getframe()/8) % 9), pers.getladocelda()*y,pers.getladocelda(), pers.getladocelda() );
    pers.sumarframe();
    pers.setdireccion(3);
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
   pers.setposicionsprite(pers.getPosicionF());
       int x=1;
       int y=8;
pers.setsubrectsprite(pers.getladocelda()* (x + (pers.getframe()/8) % 9), pers.getladocelda()*y,pers.getladocelda(), pers.getladocelda() );
        pers.sumarframe();
    pers.setdireccion(1);
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
    pers.setposicionsprite(pers.getPosicionF());
       int x=1;
       int y=10;
pers.setsubrectsprite(pers.getladocelda()* (x + (pers.getframe()/8) % 9), pers.getladocelda()*y,pers.getladocelda(), pers.getladocelda() );
        pers.sumarframe();
    pers.setdireccion(4);
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

void managerpersonaje::Asignarpersonajes(personaje& pers){
pers.setsprite();

}


void managerpersonaje::mostrarpersonaje(personaje& pers,sf::RenderWindow& window) {
        window.draw(pers.getsprite());
    }
