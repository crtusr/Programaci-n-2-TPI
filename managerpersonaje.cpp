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
  caminoIndice = 0;
}

void managerpersonaje::resetCaminoIndice()
{
  caminoIndice = 0;
}

int managerpersonaje::moverpersonaje(personaje &pers, const int *dir)
{
  if(dir[caminoIndice] == -1)
    return 0;
  int sentido, x, y;
  if(dir[caminoIndice] != -1 && ((dir[caminoIndice] != 0 &&(!pers.getblockaccion()))||((pers.getblockaccion())&&(pers.getdireccion() == dir[caminoIndice]))))
  {
    if(pers.getaccion()!=ACTIVO)
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
    pers.setaccion(SIN_ACCION);
    pers.setframe(0);
  }
  if(pers.getaccion() == 0)
  {
    pers.sumarframe();
  }
  if(dir[caminoIndice] == -1)
  {
    pers.setblockaccion(false);
    pers.setaccion(SIN_ACCION);
    pers.setframe(0);
    pers.setdireccion(0);
    return 0;
  }
  pers.setaccion(ACTIVO);
  return 1;

}

void managerpersonaje::moverpersonaje(personaje& pers)
{
  if((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)&&(!pers.getblockaccion()))||((pers.getblockaccion())&&(pers.getdireccion()==2)))
  {
    if(pers.getaccion()!=1)
    {
      pers.setframe(0);
    }
    pers.setaccion(1);
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


int managerpersonaje::comprobarlugar(int x,int y,vector<personaje> pers)
{
    int i;
for(i=0;i<5;i++){

    if((pers[i].getPosxPxl()==x)&&(pers[i].getPosyPxl()==y)){
        return 1;
        }
    }
  return -1;
}

void managerpersonaje::actualizarpersonaje(vector<personaje>& pers)
{
int i;
  for(i=0;i<5;i++)
  {
  if(pers[i].getaccion()==0)
  {
    int aux=0;
    int aux2=0;
    switch(pers[i].getdireccion()){
    case 1: aux=22; break;
    case 2: aux=25; break;
    case 3: aux=23; break;
    case 4: aux=24; break;
    }
    if(pers[i].getframe()>64){ pers[i].setframe(0);}
    if(pers[i].getframe()>32){ aux2=1;}
    if(pers[i].getframe()<=32){ aux2=0;}

    pers[i].setsubrectsprite(64*aux2,64*aux,64,64);
    pers[i].sumarframe();
  }
 }

}
