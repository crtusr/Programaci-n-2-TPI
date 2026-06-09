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
  cantidad_pers = 0;
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
  int sentido = 1, x, y;
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
        pers.setsumresposx(sentido);
        x = 0;
        y = 11;
        break;
      case IZQUIERDA:
        pers.setsumresposx(sentido * -1);
        x = 0;
        y = 9;
        break;
      case ARRIBA:
        pers.setsumresposy(sentido * -1);
        x = 0;
        y = 8;
        break;
      case ABAJO:
        pers.setsumresposy(sentido);
        x = 0;
        y = 10;
        break;
    }
    pers.setposicionsprite(pers.getPosicionF());
    pers.setsubrectsprite(pers.getladocelda()* (x + (pers.getframe()/8) % 9), pers.getladocelda()*y,pers.getladocelda(), pers.getladocelda() );
    pers.sumarframe();
    pers.setdireccion(dir[caminoIndice]);
  }
  if((pers.getPosxPxl() + pers.getPosyPxl()) % pers.getladocelda() == 0 && dir[caminoIndice] != -1)
  {
    caminoIndice++;
    pers.setblockaccion(false);
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
  if((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)&&(!pers.getblockaccion()))||((pers.getblockaccion())&&(pers.getdireccion()==DERECHA)))
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
    pers.setdireccion(DERECHA);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)&&(!pers.getblockaccion())||(pers.getblockaccion())&&(pers.getdireccion()==IZQUIERDA))
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
    pers.setdireccion(IZQUIERDA);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)&&(!pers.getblockaccion())||(pers.getblockaccion())&&(pers.getdireccion()==ARRIBA))
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
    pers.setdireccion(ARRIBA);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)&&(!pers.getblockaccion())||(pers.getblockaccion())&&(pers.getdireccion()==ABAJO))
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
    pers.setdireccion(ABAJO);

  }
  if(pers.getframe()>=pers.getladocelda())
  {
    pers.setblockaccion(false);
    pers.setaccion(0);
    pers.setframe(0);
  }

}




void managerpersonaje::mostrarpersonaje(vector<personaje>& pers,RenderWindow& window) {
       int i;
        for(i=0;i<cantidad_pers;i++)
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
     if(actual>=cantidad_pers)
     {
       actual=0;
     }
   }
   if(cont>0){cont++;}
   if(cont>10){cont=0;}
}

void managerpersonaje::cambiardireccion(vector<personaje>& pers, int dir)
{
  if(dir == ARRIBA)
    pers[actual].setdireccion(ARRIBA);
  if(dir == ABAJO)
    pers[actual].setdireccion(ABAJO);
  if(dir == IZQUIERDA) 
    pers[actual].setdireccion(IZQUIERDA);
  if(dir == DERECHA) 
    pers[actual].setdireccion(DERECHA);
}

int managerpersonaje::getactual()
{
  return actual;
}

  int managerpersonaje::getcantidad()
  {
  return cantidad_pers;
  }


  void managerpersonaje::setcantidad(int cantidad)
  {
  cantidad_pers=cantidad;
  }

int managerpersonaje::comprobarlugar(int x,int y,vector<personaje> pers)
{
    int i;
for(i=0;i<cantidad_pers;i++){

    if((pers[i].getPosxPxl()==x)&&(pers[i].getPosyPxl()==y))
        {
        return 1;
        }
    }
  return -1;
}
void managerpersonaje::actualizarpersonaje(vector<personaje>& pers)
{
  int i;
  for(i=0;i<cantidad_pers;i++)
  {
    if(pers[i].getaccion()==0)
    {
      int ladoCelda = pers[i].getladocelda();
      int nDeFilaSprite = 0, nDeColumnaSprite = 0;
      switch(pers[i].getdireccion()){
        case ARRIBA: nDeFilaSprite = 22; break;
        case DERECHA: nDeFilaSprite = 25; break;
        case ABAJO: nDeFilaSprite = 24; break;
        case IZQUIERDA: nDeFilaSprite = 23; break;
      }
      nDeColumnaSprite = (pers[i].getframe() / 32) % 2;

      pers[i].setsubrectsprite(ladoCelda * nDeColumnaSprite, ladoCelda * nDeFilaSprite,
                               ladoCelda, ladoCelda);
      pers[i].sumarframe();
    }
  }

}
int managerpersonaje::contarPersonajesActivos(vector<personaje>& pers)
{
  int cuenta = 0;

  for(int i = 0; i < pers.size(); i++)
    if(pers[i].getHp()) cuenta++;

  return cuenta;
}

void managerpersonaje::Asignarpersonajes(personaje& pers, TIPO_PERSONAJE tipo, int x, int y)
{
    int px = x * pers.getladocelda();
    int py = y * pers.getladocelda();

    pers.setposx(px);
    pers.setposy(py);
    pers.setposicionsprite(sf::Vector2f(px, py));

    pers.setdireccion(ABAJO);
    pers.setaccion(0);
    pers.setframe(0);

    pers.setsprite(); // inicializa sprite

    // recorte inicial visible
    pers.setsubrectsprite(
        0,
        0,
        pers.getladocelda(),
        pers.getladocelda()
    );
}


