#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include "managerpersonaje.h"

using namespace std;
using namespace sf;

void managerpersonaje::moverpersonaje(personaje& pers)
{
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
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)&&(!pers.getblockaccion())||(pers.getblockaccion())&&(pers.getdireccion()==3))
  {
    if(pers.getaccion()!=1)
    {
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
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)&&(!pers.getblockaccion())||(pers.getblockaccion())&&(pers.getdireccion()==1))
  {
    if(pers.getaccion()!=1)
    {
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
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)&&(!pers.getblockaccion())||(pers.getblockaccion())&&(pers.getdireccion()==4))
  {
    if(pers.getaccion()!=1)
    {
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

  }
  if(pers.getframe()>=pers.getladocelda())
  {
    pers.setblockaccion(false);
    pers.setaccion(0);
    pers.setframe(0);
  }
  if(pers.getaccion()==0)
  {
    pers.sumarframe();
  }
  pers.setaccion(1);
}


void managerpersonaje::Asignarpersonajes(personaje& pers)
{
  pers.setsprite();
}


void managerpersonaje::mostrarpersonaje(vector<personaje>& pers,RenderWindow& window) {
       int i;
        for(i=0;i<5;i++)
        {
           window.draw(pers[i].getsprite());
        }
    }

void managerpersonaje::secuencia(personaje& pers)
{
  pers.setaccion(1);
  pers.setdireccion(2);
  pers.setblockaccion(true);
  moverpersonaje(pers);
}

void managerpersonaje::cambiarpersonaje(personaje& pers)
{
   if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)&&(pers.getblockaccion()==false)&&(cont==0))
   {
     cont++;
     actual++;
     if(actual>=5)
     {
       actual=0;
     }
   }
   if(cont>0){cont++;}
   if(cont>10){cont=0;}
}

  void managerpersonaje::cambiardireccion(vector<personaje>& pers){
if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){ pers[actual].setdireccion(1);}
if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){pers[actual].setdireccion(2);}
if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)){ pers[actual].setdireccion(3);}
if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)){ pers[actual].setdireccion(4);}

  }

int managerpersonaje::getactual()
{
  return actual;
}
