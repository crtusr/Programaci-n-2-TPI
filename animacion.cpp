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
pers_atk[manager.getactual()].setaccion(ATAQUE_ESPADA);
atk_activo=true;
anim_frame=0;
atk_frame=0;
break;
case 2:
pers_atk[manager.getactual()].setaccion(ATAQUE_ESPADA);
atk_activo=true;
anim_frame=-10;
atk_frame=0;
break;
case 3:
pers_atk[manager.getactual()].setaccion(ATAQUE_GRANADA);
atk_activo=true;aux_x=0;aux_y=0;
anim_frame=-95;
atk_frame=-40;
break;
case 4:
pers_atk[manager.getactual()].setaccion(ATAQUE_ARCO);
atk_activo=true;aux_x=0;aux_y=0;
anim_frame=ataque.getdistancia()*-12;
atk_frame=-40;
break;
case 5:
pers_atk[manager.getactual()].setaccion(ATAQUE_GRANADA);
atk_activo=true;aux_x=0;aux_y=0;
anim_frame=-95;
atk_frame=-40;
break;
case 6:
pers_atk[manager.getactual()].setaccion(ATAQUE_GRANADA);
atk_activo=true;
anim_frame=-95;
atk_frame=-40;
break;
case 7:
pers_atk[manager.getactual()].setaccion(BUFEO_ARMADURA);
atk_activo=true;
anim_frame=-20;
atk_frame=0;
break;
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
    case BUFEO_ARMADURA:
    v_posx[i]=pers_atk[ataque.getimpacto(cont)].getPosxPxl();
    v_posy[i]=pers_atk[ataque.getimpacto(cont)].getPosyPxl();
    break;
    }
    tipodeataque=ataque.gettipodeataque();
    cont++;
  }
}
}

bool Animacion::mostraranimacion(RenderWindow& window){

    int x=0;
    int y=0;

    if(tipodeataque==DANIO){y=0;}
    if(tipodeataque==CURACION){y=1;}
    if(tipodeataque==BUFEO_ARMADURA){y=2;}
    if(anim_frame<=0){x=-1;}
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
        if(anim_frame>80){return false;}
    }
anim_frame++;
return true;
}

void Animacion::mostrarvida(RenderWindow& window,vector<personaje>& pers,int color){
  for(int i=0;i<pers.size();i++){
   if(pers[i].getaccion()!=MUERTO||pers[i].getframe()<40)
   {
    rectangulo.setPosition(Vector2f(pers[i].getPosxPxl()+25,pers[i].getPosyPxl()+56));
    if(color==1){rectangulo.setFillColor(sf::Color(0, 0, 255, 160));}
    if(color==2){rectangulo.setFillColor(sf::Color(255, 0, 0, 160));}
    float aux1=pers[i].getHpReal();
    float aux2=pers[i].getMaxHpReal();
    float auxf = aux1/aux2;
    float aux3 = 55*auxf;
    string salud = to_string(pers[i].getHpReal());
    salud += "-";
    salud += to_string(pers[i].getMaxHpReal());
    barradevida.setSize(Vector2f(aux3,5));
    barradevida.setPosition(Vector2f(pers[i].getPosxPxl()+7,pers[i].getPosyPxl()+10));
    barradevida.setFillColor(Color::Green);
    text.setString(salud);
    text.setPosition(Vector2f(pers[i].getPosxPxl()+10,pers[i].getPosyPxl()-6));
    text.setFillColor(Color::Black);
    fondodevida.setPosition(Vector2f(pers[i].getPosxPxl()+7,pers[i].getPosyPxl()+10));
    window.draw(fondodevida);
    window.draw(barradevida);
    window.draw(rectangulo);
    window.draw(text);
    }
  }
}


bool Animacion::mostrarataque(personaje& pers,RenderWindow& window,Ataque& ataque){
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
        spt_ataque2.setPosition(sf::Vector2f(pers.getPosxPxl()-64,pers.getPosyPxl()-64));
        spt_ataque2.setTextureRect(sf::IntRect(sf::Vector2i(192*x, 192*y),sf::Vector2i(192, 192)));
        window.draw(spt_ataque2);
    }

if(ataque.getopciondeataque()==3&&atk_activo==true){
        if(atk_frame<=48&&atk_frame>0){
    switch(pers.getdireccion()){
    case ARRIBA:    aux_y-=4; break;
    case DERECHA:   aux_x+=4; break;
    case ABAJO:     aux_y+=4; break;
    case IZQUIERDA: aux_x-=4; break;
     }
    }
    if(atk_frame<=0){x=-1;}
    if(atk_frame>0){x=0;}
    if(atk_frame>10){x=1;}
    if(atk_frame>20){x=2;}
    if(atk_frame>30){x=3;}
    if(atk_frame>40){x=4;}
    if(atk_frame>60){x=5;}
    if(atk_frame>65){x=6;}
    if(atk_frame>70){x=7;}
    if(atk_frame>80){x=8;}
    if(atk_frame>90){x=9;}
        spt_ataque3.setPosition(sf::Vector2f(pers.getPosxPxl()+aux_x-64,pers.getPosyPxl()+aux_y-64));
        spt_ataque3.setTextureRect(sf::IntRect(sf::Vector2i(192*x, 192*0),sf::Vector2i(192, 192)));
        window.draw(spt_ataque3);
    }


if(ataque.getopciondeataque()==4&&atk_activo==true){
    int x=0;
    int y=0;
    if(atk_frame<=48&&atk_frame>0){
        switch(pers.getdireccion()){
    case ARRIBA:    aux_y-=16;x=3; break;
    case DERECHA:   aux_x+=16;x=0; break;
    case ABAJO:     aux_y+=16;x=1; break;
    case IZQUIERDA: aux_x-=16;x=2; break;
     }
     int dist = ataque.getdistancia()*64;
        spt_ataque4.setPosition(sf::Vector2f(pers.getPosxPxl()+aux_x,pers.getPosyPxl()+aux_y));
        spt_ataque4.setTextureRect(sf::IntRect(sf::Vector2i(64*x,64*y),sf::Vector2i(64, 64)));
        if(aux_y>=dist*-1&&aux_y<=dist&&aux_x>=dist*-1&&aux_x<=dist)
        {
         window.draw(spt_ataque4);
        }
    }

}

if(ataque.getopciondeataque()==5&&atk_activo==true){
        if(atk_frame<=48&&atk_frame>0){
    switch(pers.getdireccion()){
    case ARRIBA:    aux_y-=4; break;
    case DERECHA:   aux_x+=4; break;
    case ABAJO:     aux_y+=4; break;
    case IZQUIERDA: aux_x-=4; break;
     }
    }
    if(atk_frame<=0){x=-1;}
    if(atk_frame>0){x=0;}
    if(atk_frame>10){x=1;}
    if(atk_frame>20){x=2;}
    if(atk_frame>30){x=3;}
    if(atk_frame>40){x=4;}
    if(atk_frame>60){x=5;}
    if(atk_frame>65){x=6;}
    if(atk_frame>70){x=7;}
    if(atk_frame>80){x=8;}
    if(atk_frame>90){x=9;}
        spt_curacion1.setPosition(sf::Vector2f(pers.getPosxPxl()+aux_x-64,pers.getPosyPxl()+aux_y-64));
        spt_curacion1.setTextureRect(sf::IntRect(sf::Vector2i(192*x, 192*0),sf::Vector2i(192, 192)));
        window.draw(spt_curacion1);
    }

    if(ataque.getopciondeataque()==6&&atk_activo==true){
     int x;
    if(atk_frame<=0){x=-1;}
    if(atk_frame>0){x=0;}
    if(atk_frame>10){x=1;}
    if(atk_frame>20){x=2;}
    if(atk_frame>30){x=3;}
    if(atk_frame>40){x=4;}
    if(atk_frame>60){x=5;}
    if(atk_frame>65){x=6;}
    if(atk_frame>70){x=7;}
    if(atk_frame>80){x=8;}
    if(atk_frame>90){x=9;}
        spt_curacion1.setPosition(sf::Vector2f(pers.getPosxPxl()-64,pers.getPosyPxl()-64));
        spt_curacion1.setTextureRect(sf::IntRect(sf::Vector2i(192*x, 192*0),sf::Vector2i(192, 192)));
        window.draw(spt_curacion1);
    }

   if(atk_frame>100){atk_activo=false;return false;}
   atk_frame++;
   return true;
}

void Animacion::iniciartrancicion(){
trancicion=true;

}


void Animacion::animartrancicion(RenderWindow& window){
    if(trancicion==true){
 frame_trancicion+=20;
 int x=frame_trancicion;
 if(frame_trancicion<=2000&&frame_trancicion>1000){x=1000;}
 if(frame_trancicion>2000){x-=1000;}
  barraoscura.setPosition(Vector2f(0,-1100+x));
if(frame_trancicion>=4000){
  frame_trancicion=0;
  trancicion=false;
}
window.draw(barraoscura);
        }

}
