#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include "ataque.h"

using namespace std;
using namespace sf;

Sprite ataque::getsprite(){
    return sprite;
    }

void ataque::ataque1(int posx,int posy,int direccion,RenderWindow& window){
switch(direccion){
case 1:
 v_dirx[0]=posx;
 v_diry[0]=posy-64;
 sprite.setPosition(sf::Vector2f(v_dirx[0],v_diry[0]));
 window.draw(sprite);
break;
case 2:
v_dirx[0]=posx+64;
v_diry[0]=posy;
sprite.setPosition(sf::Vector2f(v_dirx[0],v_diry[0]));
window.draw(sprite);
break;
case 3:
v_dirx[0]=posx-64;
v_diry[0]=posy;
sprite.setPosition(sf::Vector2f(v_dirx[0],v_diry[0]));
window.draw(sprite);
break;
case 4:

v_dirx[0]=posx;
 v_diry[0]=posy+64;
sprite.setPosition(sf::Vector2f(v_dirx[0],v_diry[0]));
window.draw(sprite);
break;
default:
break;
}


}

void ataque::ataque2(int posx,int posy,int direccion,RenderWindow& window){
switch(direccion){
int i;
case 1:

v_dirx[0]=posx-64;
v_diry[0]=posy-64;
for(i=0;i<3;i++)
{

 sprite.setPosition(sf::Vector2f(v_dirx[0],v_diry[0]));
 window.draw(sprite);
 v_dirx[0]+=64;
}

break;
case 2:
v_dirx[0]=posx+64;
v_diry[0]=posy-64;
for(i=0;i<3;i++)
{

 sprite.setPosition(sf::Vector2f(v_dirx[0],v_diry[0]));
 window.draw(sprite);
v_diry[0]+=64;
}
break;
case 3:
v_dirx[0]=posx-64;
v_diry[0]=posy+64;
for(i=0;i<3;i++)
{

 sprite.setPosition(sf::Vector2f(v_dirx[0],v_diry[0]));
 window.draw(sprite);
v_diry[0]-=64;
}
break;
case 4:
v_dirx[0]=posx-=64;
 v_diry[0]=posy+64;
for(i=0;i<3;i++)
{

 sprite.setPosition(sf::Vector2f(v_dirx[0],v_diry[0]));
 window.draw(sprite);
 v_dirx[0]+=64;
}
break;
default:
break;
}


}

void ataque::ataque3(){


}

void ataque::ataque4(){


}

void ataque::prepararataque(int posx,int posy,int direccion,RenderWindow& window){

if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1)){opc=1;}
if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2)){ opc=2;}
switch(opc){
case 1:ataque1(posx,posy,direccion,window);
break;
case 2:ataque2(posx,posy,direccion,window);
break;
}
}
