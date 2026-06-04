#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include "managerpersonaje.h"
#include "constantes.h"

using namespace std;
using namespace sf;

managerpersonaje::managerpersonaje()
{
  cont = 0;
  actual = 0;
  caminoIndice = 255;
}

void managerpersonaje::resetCaminoIndice()
{
  caminoIndice = 0;
}

void managerpersonaje::moverpersonaje(personaje &pers, const int *dir)
{
  int sentido, x, y;
  if(dir[caminoIndice] != -1 && ((dir[caminoIndice] != 0 &&(!pers.getblockaccion()))||((pers.getblockaccion())&&(pers.getdireccion() == dir[caminoIndice]))))
  {
    if(pers.getaccion()!=1)
    {
      pers.setframe(0);
    }
    pers.setblockaccion(true);
    switch(dir[caminoIndice])
    {
      case DERECHA:
        sentido = 1;
        pers.setsumresposx(sentido);
        x = 1;
        y = 11;
        break;
      case IZQUIERDA:
        sentido = -1;
        pers.setsumresposx(sentido);
        x = 1;
        y = 9;
        break;
      case ARRIBA:
        sentido = -1;
        pers.setsumresposy(sentido);
        x = 1;
        y = 8;
        break;
      case ABAJO:
        sentido = 1;
        pers.setsumresposy(sentido);
        x = 1;
        y = 10;
        break;
    }
    pers.setposicionsprite(pers.getPosicionF());
    pers.setsubrectsprite(pers.getladocelda()* (x + (pers.getframe()/8) % 9), pers.getladocelda()*y,pers.getladocelda(), pers.getladocelda() );
    pers.sumarframe();
    pers.setdireccion(dir[caminoIndice]);
  }
  if(pers.getframe()>=pers.getladocelda() && dir[caminoIndice] != -1)
  {
    caminoIndice++;
    pers.setblockaccion(false);
    pers.setaccion(0);
    pers.setframe(0);
  }
  if(pers.getaccion()==0)
  {
    pers.sumarframe();
  }
  if(dir[caminoIndice] == -1)
    pers.setdireccion(0);
  pers.setaccion(1);
}


void managerpersonaje::Asignarpersonajes(personaje& pers)
{
  pers.setsprite();
}


void managerpersonaje::mostrarpersonaje(personaje& pers,sf::RenderWindow& window) 
{
  window.draw(pers.getsprite());
}

void managerpersonaje::secuencia(personaje& pers)
{
  pers.setaccion(1);
  pers.setdireccion(2);
  pers.setblockaccion(true);
  //moverpersonaje(pers);
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

int managerpersonaje::getactual()
{
  return actual;
}
