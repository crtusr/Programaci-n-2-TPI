#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include "ataque.h"
#include "constantes.h"

using namespace std;
using namespace sf;

Sprite ataque::getsprite()
{
  return sprite;
}

void ataque::ataque1(int direccion,RenderWindow& window,vector<personaje>& pers,managerpersonaje& manager)
{
  int aux;
  switch(direccion){
  case ARRIBA:
    v_dirx[0]=0;
    v_diry[0]=-64;
    break;
  case DERECHA:
    v_dirx[0]=64;
    v_diry[0]=0;
    break;

  case ABAJO:
    v_dirx[0]=-64;
    v_diry[0]=0;
    break;

  case IZQUIERDA:
    v_dirx[0]=0;
    v_diry[0]=64;
    break;

  default:
    break;

}
  sprite.setPosition(sf::Vector2f(pers[manager.getactual()].getPosxPxl()+v_dirx[0],pers[manager.getactual()].getPosyPxl()+v_diry[0]));
  sprite2.setPosition(sf::Vector2f(pers[manager.getactual()].getPosxPxl()+v_dirx[0],pers[manager.getactual()].getPosyPxl()+v_diry[0]));
  aux=manager.comprobarlugar(pers[manager.getactual()].getPosxPxl()+v_dirx[0],pers[manager.getactual()].getPosyPxl()+v_diry[0],pers);
  if(aux==-1)
    window.draw(sprite);
  if(aux==1)
    window.draw(sprite2);
}

void ataque::ataque2(int direccion,RenderWindow& window,vector<personaje>& pers,managerpersonaje& manager)
{
  int i;
  int aux;
  switch(direccion)
  {
    case ARRIBA:
      v_dirx[0]=-64;
      v_dirx[1]=0;
      v_dirx[2]=64;
      
      v_diry[0]=-64;
      v_diry[1]=-64;
      v_diry[2]=-64;
      break;
    case DERECHA:
      v_dirx[0]=64;
      v_dirx[1]=64;
      v_dirx[2]=64;
      
      v_diry[0]=-64;
      v_diry[1]=0;
      v_diry[2]=64;
      break;
    case IZQUIERDA:
      v_dirx[0]=-64;
      v_dirx[1]=-64;
      v_dirx[2]=-64;
      
      v_diry[0]=64;
      v_diry[1]=0;
      v_diry[2]=-64;
      break;
    case ABAJO:
      v_dirx[0]=-64;
      v_dirx[1]=0;
      v_dirx[2]=64;
      
      v_diry[0]=64;
      v_diry[1]=64;
      v_diry[2]=64;
      break;
    default:
      break;
  }
  for(i=0;i<3;i++)
  {
    sprite.setPosition(sf::Vector2f(pers[manager.getactual()].getPosxPxl()+v_dirx[i],pers[manager.getactual()].getPosyPxl()+v_diry[i]));
    sprite2.setPosition(sf::Vector2f(pers[manager.getactual()].getPosxPxl()+v_dirx[i],pers[manager.getactual()].getPosyPxl()+v_diry[i]));
    aux=manager.comprobarlugar(pers[manager.getactual()].getPosxPxl()+v_dirx[i],pers[manager.getactual()].getPosyPxl()+v_diry[i],pers);
    if(aux==-1)
    {
      window.draw(sprite);
    }
    if(aux==1)
    {
      window.draw(sprite2);
    }
  }
}

void ataque::ataque3(){


}

void ataque::ataque4(){


}

void ataque::prepararataque(int direccion,RenderWindow& window,vector<personaje>& pers,managerpersonaje& manager)
{
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
    opc=1;
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
    opc=2;
  switch(opc)
  {
    case 1:
      ataque1(direccion,window,pers,manager);
      break;
    case 2:
      ataque2(direccion,window,pers,manager);
      break;
  }
}

