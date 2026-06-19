#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include "animacion.h"
#include "constantes.h"

using namespace std;
using namespace sf;

void Animacion::asignaranimacion(vector<personaje>& pers,int* impactos ,int* v_danios,int cant){
int cont=0;

for(int i=0; i<6; i++){
  if(!anim_activa[i]&&cont<cant){
    anim_activa[i]=true;
    danios[i]=v_danios[cont];
    v_posx[i]=pers[impactos[cont]].getPosxPxl();
    v_posy[i]=pers[impactos[cont]].getPosyPxl();
    cont++;
  }
}
anim_frame=0;
}
void Animacion::mostraranimacion(RenderWindow& window){
    int x;
    int y;
    if(anim_frame==0){x=0;y=0;}
    if(anim_frame>10){x=3;y=0;}
    if(anim_frame>20){x=4;y=0;}
    if(anim_frame>30){x=5;y=0;}
    if(anim_frame>40){x=6;y=0;}
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
