#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include "animacion.h"
#include "constantes.h"

using namespace std;
using namespace sf;

 void Animacion::asignaranimacion(vector<personaje>& pers_atk,vector<personaje>& pers_def,Ataque& ataque,managerpersonaje& manager){
int cont=0;
anim_frame=0;
switch(ataque.getopciondeataque()){
case 1:
pers_atk[manager.getactual()].setaccion(ATAQUE_ESPADA);break;
case 2:
pers_atk[manager.getactual()].setaccion(ATAQUE_ESPADA);break;
case 3:
pers_atk[manager.getactual()].setaccion(ATAQUE_GRANADA);break;
case 4:
pers_atk[manager.getactual()].setaccion(ATAQUE_ARCO);break;
case 5:
pers_atk[manager.getactual()].setaccion(ATAQUE_GRANADA);break;
}


pers_atk[manager.getactual()].setframe(0);

for(int i=0; i<6; i++){
  if(!anim_activa[i]&&cont<ataque.getcantidadimpactos()){
    anim_activa[i]=true;
    danios[i]=ataque.getdanio(cont);
    switch(ataque.gettipodeataque()){
    case DANIO:
    v_posx[i]=pers_def[ataque.getimpacto(cont)].getPosxPxl();
    v_posy[i]=pers_def[ataque.getimpacto(cont)].getPosyPxl();

    break;
    case CURACION:
    v_posx[i]=pers_atk[ataque.getimpacto(cont)].getPosxPxl();
    v_posy[i]=pers_atk[ataque.getimpacto(cont)].getPosyPxl();
    break;
    }
    tipodeataque=ataque.gettipodeataque();
    cont++;
  }
}
}

void Animacion::mostraranimacion(RenderWindow& window){

    int x=0;
    int y=0;
    if(tipodeataque==DANIO){y=0;}
     if(tipodeataque==CURACION){y=1;}

    if(anim_frame>0){x=0;}
    if(anim_frame>10){x=1;}
    if(anim_frame>20){x=2;}
    if(anim_frame>30){x=3;}
    if(anim_frame>40){x=4;}
    if(anim_frame>40){x=5;}
    sprite.setTextureRect(sf::IntRect(sf::Vector2i(64*x,64*y),sf::Vector2i(64,64)));

    for(int i=0; i<6; i++){
        if(anim_activa[i]){
            sprite.setPosition(sf::Vector2f(v_posx[i],v_posy[i]));
            window.draw(sprite);
        if(anim_frame>60){anim_activa[i]=false;}
        }
    }

anim_frame++;

}

void Animacion::mostrarvida(RenderWindow& window,vector<personaje>& pers){

  for(int i=0;i<pers.size();i++){
    string salud = to_string(pers[i].getHpReal());
    text.setString(salud);
    text.setPosition(Vector2f(pers[i].getPosxPxl()+10,pers[i].getPosyPxl()-10));
    text.setFillColor(Color::Black);
    window.draw(text);
  }
}
