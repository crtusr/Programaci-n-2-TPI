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
atk_frame=0;
switch(ataque.getopciondeataque()){
case 1:
pers_atk[manager.getactual()].setaccion(ATAQUE_ESPADA);break;
case 2:
pers_atk[manager.getactual()].setaccion(ATAQUE_ESPADA);
atk_activo=true;break;
case 3:
pers_atk[manager.getactual()].setaccion(ATAQUE_GRANADA);
atk_activo=true;aux_x=0;aux_y=0;break;
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
    if(anim_frame>50){x=5;}

    sprite.setTexture(textura);
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

  for(size_t i=0;i<pers.size();i++){
    if(pers[i].getHpReal() == 0)
      continue;
    string salud = to_string(pers[i].getHpReal());
    text.setString(salud);
    text.setPosition(Vector2f(pers[i].getPosxPxl()+10,pers[i].getPosyPxl()-10));
    text.setFillColor(Color::Black);
    window.draw(text);
  }
}

void Animacion::mostrarataque(personaje& pers,RenderWindow& window,Ataque& ataque){
    int x;
    int y;

if(ataque.getopciondeataque()==2&&atk_activo==true){
    switch(pers.getdireccion()){
    case ARRIBA:    y=0; break;
    case DERECHA:   y=3; break;
    case ABAJO:     y=2; break;
    case IZQUIERDA: y=1; break;
   }
    if(atk_frame>0){x=0;}
    if(atk_frame>10){x=1;}
    if(atk_frame>20){x=2;}
    if(atk_frame>30){x=3;}
    if(atk_frame>40){x=4;}
    if(atk_frame>50){x=5;}

        spt_ataque2.setTexture(tex_ataque2);
        spt_ataque2.setPosition(sf::Vector2f(pers.getPosxPxl()-64,pers.getPosyPxl()-64));
        spt_ataque2.setTextureRect(sf::IntRect(sf::Vector2i(192*x, 192*y),sf::Vector2i(192, 192)));
        window.draw(spt_ataque2);
    }

if(ataque.getopciondeataque()==3&&atk_activo==true){
        if(atk_frame<=48){
    switch(pers.getdireccion()){
    case ARRIBA:    aux_y-=4; break;
    case DERECHA:   aux_x+=4; break;
    case ABAJO:     aux_y+=4; break;
    case IZQUIERDA: aux_x-=4; break;
     }
    }
    if(atk_frame>0){x=0;}
    if(atk_frame>10){x=1;}
    if(atk_frame>20){x=2;}
    if(atk_frame>30){x=3;}
    if(atk_frame>40){x=4;}
    if(atk_frame>48){x=5;}
    if(atk_frame>65){x=6;}
    if(atk_frame>70){x=7;}
    if(atk_frame>80){x=8;}
    if(atk_frame>90){x=9;}

        spt_ataque3.setTexture(tex_ataque3);
        spt_ataque3.setPosition(sf::Vector2f(pers.getPosxPxl()+aux_x-64,pers.getPosyPxl()+aux_y-64));
        spt_ataque3.setTextureRect(sf::IntRect(sf::Vector2i(192*x, 192*0),sf::Vector2i(192, 192)));
        window.draw(spt_ataque3);
    }

   if(atk_frame>90){atk_activo=false;}
   atk_frame++;
}
