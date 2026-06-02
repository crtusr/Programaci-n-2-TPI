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
    bool yaActuo = false;
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


    sprite.setTextureRect(sf::IntRect(
        sf::Vector2i(ladoCelda*0, ladoCelda*0),      // posición inicial dentro del spritesheet---Vector2i:pertenece a la libreria de SFLM y contiene 2 vectores
        sf::Vector2i(ladoCelda, ladoCelda)         // tamaño del recorte
    ));

    }


    // Getters
    int getPosx();            //posx tiene que devolver la posición en la grilla
    int getPosy();            //posx tiene que devolver la posición en la grilla
    int getPosxPxl();
    int getPosyPxl();
    int getdireccion();
    int getaccion();
    bool getblockaccion();
    int getframe();
    int getladocelda();
    Sprite getsprite();
    Vector2f getPosicionF();
    Vector2i getPosicionI();


    void setaccion(int acc);
    void setdireccion(int drc);
    void setframe(int fra);
    void setblockaccion(bool block);
    void setposx(int px);
    void setposy(int py);
    void setsumresposx(int px);
    void setsumresposy(int py);
    void sumarframe();
    void setposicionsprite(Vector2f pos);
    void setsubrectsprite(int x1,int y1,int x2,int y2);
    void setsprite();






};
#endif // PERSONAJE_H_INCLUDED

