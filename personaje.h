#ifndef PERSONAJE_H_INCLUDED
#define PERSONAJE_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include <string>
#include "grilla.h"
#include "celda.h"
using namespace std;
using namespace sf;




class personaje {
private:
    int posx = 0;
    int posy = 0;
    int direccion = 0;
    int accion = 0;
    bool blokaccion = false;
    int frame = 0;
    int ladoCelda;
    Grilla *grilla;
    Sprite sprite;

    sf::Texture textura;

public:
    // Constructor
    personaje(Grilla *g) : sprite(textura)
      {
        grilla = g;
        ladoCelda = g->getTamCeldaPixeles();
        if (!textura.loadFromFile("imagen/character-spritesheet.png")) {
            std::cerr << "Error al cargar textura\n";
        }
        posx=ladoCelda*0;
        posy=ladoCelda*0;
        sprite.setTexture(textura);
     sprite.setPosition(sf::Vector2f(posx,posy));


    // left, top, width, height
    sprite.setTextureRect(sf::IntRect(
        sf::Vector2i(ladoCelda*0, ladoCelda*0),      // posición inicial dentro del spritesheet---Vector2i:pertenece a la libreria de SFLM y contiene 2 vectores
        sf::Vector2i(ladoCelda, ladoCelda)         // tamaño del recorte
    ));

    }


    // Getters
    int getposx() const { return posx;} //posx tiene que devolver la posición en la grilla
    int getposy() const { return posy;}
    int getdireccion() const { return direccion; }
    int getaccion() const { return accion; }
    bool getblockaccion() {return blokaccion; }
    int getframe() {return frame;}
    int getladocelda(){return ladoCelda;}
    Sprite getsprite(){return sprite;}


    void setaccion(int acc) {accion=acc;}
    void setdireccion(int drc) {direccion=drc;}
    void setframe(int fra) {frame=fra;}
    void setblockaccion(bool block) {blokaccion=block;}
    void setposx(int px){posx=px;}
    void setposy(int py){posy=py;}
    void setsumresposx(int px){posx+=px;}
    void setsumresposy(int py){posy+=py;}
    void sumarframe(){frame++;}
    void setposicionsprite(int x,int y){(sprite.setPosition(Vector2f(x,y)));}
    void setsubrectsprite(int x1,int y1,int x2,int y2){sprite.setTextureRect(IntRect(Vector2i(x1,y1),Vector2i(x2,y2)));}

    //---------arreglando---------//

        void mostrarpersonaje(sf::RenderWindow& window) {
        window.draw(sprite);
    }
//void setposx(int x) {
//    posx = x;
//    sprite->setPosition(sf::Vector2f(static_cast<float>(posx),
//                                    static_cast<float>(posy)));
//}

//void setposy(int y) {
//    posy = y;
//    sprite->setPosition(sf::Vector2f(static_cast<float>(posx),
//                                    static_cast<float>(posy)));
//    }

void cambiarsprt(int nuevox,int nuevoy);
void moverpers();



};
#endif // PERSONAJE_H_INCLUDED
