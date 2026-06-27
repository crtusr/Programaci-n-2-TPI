#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include "ataque.h"
#include "constantes.h"

using namespace std;
using namespace sf;

Sprite Ataque::getsprite()
{
  return sprite;
}
    int* Ataque::getimpactos(){return impactos;}
    int* Ataque::getdaniosimpactos(){return daniosimpactos;}
    int Ataque::getcantidadimpactos(){return cantidadimpactos;}
    int Ataque::getimpacto(int pos){return impactos[pos];}
    int Ataque::getdanio(int pos){return daniosimpactos[pos];}
    int Ataque::getdistancia(){return distancia;}
    int Ataque::gettipodeataque(){return tipodeataque;}
    int Ataque::getopciondeataque(){return opc;}
    void Ataque::setOpcionDeAtaque(int opcion) {opc = opcion;}
    string Ataque::getnombreataque(int nom){
    string nombre("ataque1");
    switch(nom){
    case 1: nombre ="ataque1";break;
    case 2: nombre ="ataque2";break;
    case 3: nombre ="ataque3";break;
    case 4: nombre ="ataque4";break;
    case 5: nombre ="curacion1";break;
    }
   return nombre;
    }

void Ataque::ataque1(int direccion,RenderWindow& window,vector<personaje>& pers_atk,vector<personaje>& pers_def,managerpersonaje& manager)
{
  tipodeataque=DANIO;
  int cont=0;
  cantidadimpactos=0;
  int v_dirx[2];
  int v_diry[2];
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

    case IZQUIERDA:
      v_dirx[0]=-64;
      v_diry[0]=0;
      break;

    case ABAJO:
      v_dirx[0]=0;
      v_diry[0]=64;
      break;

    default:
      break;

  }
  sprite.setPosition(sf::Vector2f(pers_atk[manager.getactual()].getPosxPxl()+v_dirx[0],pers_atk[manager.getactual()].getPosyPxl()+v_diry[0]));
  sprite2.setPosition(sf::Vector2f(pers_atk[manager.getactual()].getPosxPxl()+v_dirx[0],pers_atk[manager.getactual()].getPosyPxl()+v_diry[0]));
  aux=manager.comprobarlugar(pers_atk[manager.getactual()].getPosxPxl()+v_dirx[0],pers_atk[manager.getactual()].getPosyPxl()+v_diry[0],pers_def);
  if(aux==-1)
    window.draw(sprite);
  if(aux>=0)
  {
    window.draw(sprite2);
    impactos[cont]=aux;
    cont++;
    cantidadimpactos=cont;
  }
}

void Ataque::ataque2(int direccion,RenderWindow& window,vector<personaje>& pers_atk,vector<personaje>& pers_def,managerpersonaje& manager)
{
  tipodeataque=DANIO;
  int cont=0;
  cantidadimpactos=0;
  int aux;
  int v_dirx[3];
  int v_diry[3];
  switch(direccion)
  {
    case ARRIBA:
      v_dirx[0]=-64;v_dirx[1]=0;v_dirx[2]=64;
      v_diry[0]=-64;v_diry[1]=-64;v_diry[2]=-64;
      break;
    case DERECHA:
      v_dirx[0]=64;v_dirx[1]=64;v_dirx[2]=64;
      v_diry[0]=-64;v_diry[1]=0;v_diry[2]=64;
      break;
    case IZQUIERDA:
      v_dirx[0]=-64;v_dirx[1]=-64;v_dirx[2]=-64;
      v_diry[0]=64;v_diry[1]=0;v_diry[2]=-64;
      break;
    case ABAJO:
      v_dirx[0]=-64;v_dirx[1]=0;v_dirx[2]=64;
      v_diry[0]=64;v_diry[1]=64;v_diry[2]=64;
      break;
    default:
      break;
  }
  for(int i=0;i<3;i++)
  {
    sprite.setPosition(sf::Vector2f(pers_atk[manager.getactual()].getPosxPxl()+v_dirx[i],pers_atk[manager.getactual()].getPosyPxl()+v_diry[i]));
    sprite2.setPosition(sf::Vector2f(pers_atk[manager.getactual()].getPosxPxl()+v_dirx[i],pers_atk[manager.getactual()].getPosyPxl()+v_diry[i]));
    aux=manager.comprobarlugar(pers_atk[manager.getactual()].getPosxPxl()+v_dirx[i],pers_atk[manager.getactual()].getPosyPxl()+v_diry[i],pers_def);
    if(aux==-1)
    {
      window.draw(sprite);
    }
    if(aux>=0)
    {
      window.draw(sprite2);
      impactos[cont]=aux;
      cont++;
      cantidadimpactos=cont;
    }
  }

}

void Ataque::ataque3(int direccion,RenderWindow& window,vector<personaje>& pers_atk,vector<personaje>& pers_def,managerpersonaje& manager)
{
  tipodeataque=DANIO;
  int cont=0;
  cantidadimpactos=0;
  int aux;
  int v_dirx[9];
  int v_diry[9];
  switch(direccion)
  {
    case ARRIBA:
      v_dirx[0]=-64;v_dirx[1]=0;v_dirx[2]=64;v_dirx[3]=-64;v_dirx[4]=0;v_dirx[5]=64;v_dirx[6]=-64;v_dirx[7]=0;v_dirx[8]=64;
      v_diry[0]=-256;v_diry[1]=-256;v_diry[2]=-256;v_diry[3]=-192;v_diry[4]=-192;v_diry[5]=-192;v_diry[6]=-128;v_diry[7]=-128;v_diry[8]=-128;
      break;
    case DERECHA:
      v_dirx[0]=128;v_dirx[1]=128;v_dirx[2]=128;v_dirx[3]=192;v_dirx[4]=192;v_dirx[5]=192;v_dirx[6]=256;v_dirx[7]=256;v_dirx[8]=256;
      v_diry[0]=64;v_diry[1]=0;v_diry[2]=-64;v_diry[3]=64;v_diry[4]=0;v_diry[5]=-64;v_diry[6]=64;v_diry[7]=0;v_diry[8]=-64;
      break;
    case IZQUIERDA:
      v_dirx[0]=-128;v_dirx[1]=-128;v_dirx[2]=-128;v_dirx[3]=-192;v_dirx[4]=-192;v_dirx[5]=-192;v_dirx[6]=-256;v_dirx[7]=-256;v_dirx[8]=-256;
      v_diry[0]=64;v_diry[1]=0;v_diry[2]=-64;v_diry[3]=64;v_diry[4]=0;v_diry[5]=-64;v_diry[6]=64;v_diry[7]=0;v_diry[8]=-64;
      break;
    case ABAJO:
      v_dirx[0]=-64;v_dirx[1]=0;v_dirx[2]=64;v_dirx[3]=-64;v_dirx[4]=0;v_dirx[5]=64;v_dirx[6]=-64;v_dirx[7]=0;v_dirx[8]=64;
      v_diry[0]=256;v_diry[1]=256;v_diry[2]=256;v_diry[3]=192;v_diry[4]=192;v_diry[5]=192;v_diry[6]=128;v_diry[7]=128;v_diry[8]=128;
      break;
    default:
      break;
  }
  for(int i=0;i<9;i++)
  {
    sprite.setPosition(sf::Vector2f(pers_atk[manager.getactual()].getPosxPxl()+v_dirx[i],pers_atk[manager.getactual()].getPosyPxl()+v_diry[i]));
    sprite2.setPosition(sf::Vector2f(pers_atk[manager.getactual()].getPosxPxl()+v_dirx[i],pers_atk[manager.getactual()].getPosyPxl()+v_diry[i]));
    aux=manager.comprobarlugar(pers_atk[manager.getactual()].getPosxPxl()+v_dirx[i],pers_atk[manager.getactual()].getPosyPxl()+v_diry[i],pers_def);
    if(aux==-1)
    {
      window.draw(sprite);
    }
    if(aux>=0)
    {
      window.draw(sprite2);
      impactos[cont]=aux;
      cont++;
      cantidadimpactos=cont;
    }
  }
}

void Ataque::ataque4(int direccion,RenderWindow& window,vector<personaje>& pers_atk,vector<personaje>& pers_def,managerpersonaje& manager)
{
  tipodeataque=DANIO;
  distancia=0;
  int cont=0;
  cantidadimpactos=0;
  int aux;
  int v_dirx[9];
  int v_diry[9];
  switch(direccion)
  {
    case ARRIBA:
      v_dirx[0]=0;v_dirx[1]=0;v_dirx[2]=0;v_dirx[3]=0;v_dirx[4]=0;v_dirx[5]=0;v_dirx[6]=0;v_dirx[7]=0;v_dirx[8]=0;
      v_diry[0]=-64*1;v_diry[1]=-64*2;v_diry[2]=-64*3;v_diry[3]=-64*4;v_diry[4]=-64*5;v_diry[5]=-64*6;v_diry[6]=-64*7;v_diry[7]=-64*8;v_diry[8]=-64*9;
      break;
    case DERECHA:
      v_dirx[0]=64*1;v_dirx[1]=64*2;v_dirx[2]=64*3;v_dirx[3]=64*4;v_dirx[4]=64*5;v_dirx[5]=64*6;v_dirx[6]=64*7;v_dirx[7]=64*8;v_dirx[8]=64*9;
      v_diry[0]=0;v_diry[1]=0;v_diry[2]=0;v_diry[3]=0;v_diry[4]=0;v_diry[5]=0;v_diry[6]=0;v_diry[7]=0;v_diry[8]=0;
      break;
    case IZQUIERDA:
      v_dirx[0]=-64*1;v_dirx[1]=-64*2;v_dirx[2]=-64*3;v_dirx[3]=-64*4;v_dirx[4]=-64*5;v_dirx[5]=-64*6;v_dirx[6]=-64*7;v_dirx[7]=-64*8;v_dirx[8]=-64*9;
      v_diry[0]=0;v_diry[1]=0;v_diry[2]=0;v_diry[3]=0;v_diry[4]=0;v_diry[5]=0;v_diry[6]=0;v_diry[7]=0;v_diry[8]=0;
      break;
    case ABAJO:
      v_dirx[0]=0;v_dirx[1]=0;v_dirx[2]=0;v_dirx[3]=0;v_dirx[4]=0;v_dirx[5]=0;v_dirx[6]=0;v_dirx[7]=0;v_dirx[8]=0;
      v_diry[0]=64*1;v_diry[1]=64*2;v_diry[2]=64*3;v_diry[3]=64*4;v_diry[4]=64*5;v_diry[5]=64*6;v_diry[6]=64*7;v_diry[7]=64*8;v_diry[8]=64*9;
      break;
    default:
      break;
  }
  for(int i=0;i<9;i++)
  {

    sprite.setPosition(sf::Vector2f(pers_atk[manager.getactual()].getPosxPxl()+v_dirx[i],pers_atk[manager.getactual()].getPosyPxl()+v_diry[i]));
    sprite2.setPosition(sf::Vector2f(pers_atk[manager.getactual()].getPosxPxl()+v_dirx[i],pers_atk[manager.getactual()].getPosyPxl()+v_diry[i]));
    aux=manager.comprobarlugar(pers_atk[manager.getactual()].getPosxPxl()+v_dirx[i],pers_atk[manager.getactual()].getPosyPxl()+v_diry[i],pers_def);
    if(aux==-1)
    {
      window.draw(sprite);
    }
    if(aux>=0)
    {
      window.draw(sprite2);
      impactos[cont]=aux;
      cont++;
      cantidadimpactos=cont;
      i=9;
    }
    distancia++;
  }
}

void Ataque::curacion1(int direccion,RenderWindow& window,vector<personaje>& pers_atk,vector<personaje>& pers_def,managerpersonaje& manager)
{
  tipodeataque=CURACION;
  int cont=0;
  cantidadimpactos=0;
  int aux;
  int v_dirx[9];
  int v_diry[9];
  switch(direccion)
  {
    case ARRIBA:
      v_dirx[0]=-64;v_dirx[1]=0;v_dirx[2]=64;v_dirx[3]=-64;v_dirx[4]=0;v_dirx[5]=64;v_dirx[6]=-64;v_dirx[7]=0;v_dirx[8]=64;
      v_diry[0]=-256;v_diry[1]=-256;v_diry[2]=-256;v_diry[3]=-192;v_diry[4]=-192;v_diry[5]=-192;v_diry[6]=-128;v_diry[7]=-128;v_diry[8]=-128;
      break;
    case DERECHA:
      v_dirx[0]=128;v_dirx[1]=128;v_dirx[2]=128;v_dirx[3]=192;v_dirx[4]=192;v_dirx[5]=192;v_dirx[6]=256;v_dirx[7]=256;v_dirx[8]=256;
      v_diry[0]=64;v_diry[1]=0;v_diry[2]=-64;v_diry[3]=64;v_diry[4]=0;v_diry[5]=-64;v_diry[6]=64;v_diry[7]=0;v_diry[8]=-64;
      break;
    case IZQUIERDA:
      v_dirx[0]=-128;v_dirx[1]=-128;v_dirx[2]=-128;v_dirx[3]=-192;v_dirx[4]=-192;v_dirx[5]=-192;v_dirx[6]=-256;v_dirx[7]=-256;v_dirx[8]=-256;
      v_diry[0]=64;v_diry[1]=0;v_diry[2]=-64;v_diry[3]=64;v_diry[4]=0;v_diry[5]=-64;v_diry[6]=64;v_diry[7]=0;v_diry[8]=-64;
      break;
    case ABAJO:
      v_dirx[0]=-64;v_dirx[1]=0;v_dirx[2]=64;v_dirx[3]=-64;v_dirx[4]=0;v_dirx[5]=64;v_dirx[6]=-64;v_dirx[7]=0;v_dirx[8]=64;
      v_diry[0]=256;v_diry[1]=256;v_diry[2]=256;v_diry[3]=192;v_diry[4]=192;v_diry[5]=192;v_diry[6]=128;v_diry[7]=128;v_diry[8]=128;
      break;
    default:
      break;
  }
  for(int i=0;i<9;i++)
  {
    sprite3.setPosition(sf::Vector2f(pers_atk[manager.getactual()].getPosxPxl()+v_dirx[i],pers_atk[manager.getactual()].getPosyPxl()+v_diry[i]));
    sprite4.setPosition(sf::Vector2f(pers_atk[manager.getactual()].getPosxPxl()+v_dirx[i],pers_atk[manager.getactual()].getPosyPxl()+v_diry[i]));
    aux=manager.comprobarlugar(pers_atk[manager.getactual()].getPosxPxl()+v_dirx[i],pers_atk[manager.getactual()].getPosyPxl()+v_diry[i],pers_atk);
    if(aux==-1)
    {
      window.draw(sprite3);
    }
    if(aux>=0)
    {
      window.draw(sprite4);
      impactos[cont]=aux;
      cont++;
      cantidadimpactos=cont;
    }
  }
}

void Ataque::curacion2(int direccion,RenderWindow& window,vector<personaje>& pers_atk,vector<personaje>& pers_def,managerpersonaje& manager)
{
  tipodeataque=CURACION;
  int cont=0;
  cantidadimpactos=0;
  int aux;
  int v_dirx[9]={-64,0,64,-64,0,64,-64,0,64};
  int v_diry[9]={-64,-64,-64,0,0,0,64,64,64};

  for(int i=0;i<9;i++)
  {
    sprite3.setPosition(sf::Vector2f(pers_atk[manager.getactual()].getPosxPxl()+v_dirx[i],pers_atk[manager.getactual()].getPosyPxl()+v_diry[i]));
    sprite4.setPosition(sf::Vector2f(pers_atk[manager.getactual()].getPosxPxl()+v_dirx[i],pers_atk[manager.getactual()].getPosyPxl()+v_diry[i]));
    aux=manager.comprobarlugar(pers_atk[manager.getactual()].getPosxPxl()+v_dirx[i],pers_atk[manager.getactual()].getPosyPxl()+v_diry[i],pers_atk);
    if(aux==-1)
    {
      window.draw(sprite3);
    }
    if(aux>=0)
    {
      window.draw(sprite4);
      impactos[cont]=aux;
      cont++;
      cantidadimpactos=cont;
    }
  }
}

void Ataque::bufeo1(int direccion,RenderWindow& window,vector<personaje>& pers_atk,vector<personaje>& pers_def,managerpersonaje& manager)
{
  tipodeataque=BUFEO_ARMADURA;
  int cont=0;
  cantidadimpactos=0;
  int aux;
  int v_dirx=pers_atk[manager.getactual()].getPosxPxl();
  int v_diry=pers_atk[manager.getactual()].getPosyPxl();

  sprite3.setPosition(sf::Vector2f(v_dirx,v_diry));
  impactos[cont]=pers_atk[manager.getactual()].getId();
  cantidadimpactos=1;
  window.draw(sprite3);

}

void Ataque::prepararataque(int direccion,RenderWindow& window,vector<personaje>& pers_atk,vector<personaje>& pers_def,managerpersonaje& manager,int opc_atk)
{
//  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1)){opc=1;} //esto no va a estar mas cuando menu elija el ataque
//  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2)){ opc=2; } //esto no va a estar mas cuando menu elija el ataque
//  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3)){ opc=3; } //esto no va a estar mas cuando menu elija el ataque
//  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4)){ opc=4; } //esto no va a estar mas cuando menu elija el ataque
//  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num5)){ opc=5; } //esto no va a estar mas cuando menu elija el ataque
//  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num6)){ opc=6; } //esto no va a estar mas cuando menu elija el ataque
//  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num7)){ opc=7; } //esto no va a estar mas cuando menu elija el ataque

  switch(opc_atk)
  {
    case 1:
      ataque1(direccion,window,pers_atk,pers_def,manager);
      break;
    case 2:
      ataque2(direccion,window,pers_atk,pers_def,manager);
      break;
          case 3:
      ataque3(direccion,window,pers_atk,pers_def,manager);
      break;
          case 4:
      ataque4(direccion,window,pers_atk,pers_def,manager);
      break;
          case 5:
      curacion1(direccion,window,pers_atk,pers_def,manager);
      break;
         case 6:
      curacion2(direccion,window,pers_atk,pers_def,manager);
      break;
        case 7:
      bufeo1(direccion,window,pers_atk,pers_def,manager);
      break;
  }
}

