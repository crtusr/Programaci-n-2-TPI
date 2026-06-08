#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include "personaje.h"
using namespace std;
using namespace sf;

    int personaje::getId() {
        return id;
    }

    int personaje::getPosx()//posx tiene que devolver la posición en la grilla
    {
        return posx/ladoCelda;
    }

    int personaje::getPosy()//posx tiene que devolver la posición en la grilla
    {
        return posy/ladoCelda;
    }


    int personaje::getPosxPxl(){
         return posx;
    }

    int personaje::getPosyPxl(){
        return posy;
    }

    int personaje::getdireccion(){
         return direccion;
    }

    int personaje::getaccion(){
         return accion;
         }

    bool personaje::getblockaccion() {
        return blokaccion;
        }

    int personaje::getframe() {
        return frame;
        }

    int personaje::getladocelda()
    {
        return ladoCelda;
        }

    Sprite personaje::getsprite(){
        return sprite;
    }

    Vector2f personaje::getPosicionF(){
        Vector2f pos(posx,posy); return pos;
        }

    Vector2i personaje::getPosicionI(){
        Vector2i pos(posx,posy); return pos;
        }

    bool personaje::getYaActuo() {
        return yaActuo;
    }

    TIPO_PERSONAJE personaje::getTipo() {
        return tipo;
    }

        // Setters
    void personaje::setId(int nuevoId) {
        id = nuevoId;
    }

    void personaje::setaccion(int acc) {
        accion=acc;
        }

    void personaje::setdireccion(int drc) {
        direccion=drc;
        }

    void personaje::setframe(int fra) {
        frame=fra;
        }

    void personaje::setblockaccion(bool block) {
        blokaccion=block;
        }

    void personaje::setposx(int px){
        posx=px;
        }

    void personaje::setposy(int py){
        posy=py;
        }

    void personaje::setsumresposx(int px){
        posx+=px;
        }

    void personaje::setsumresposy(int py){
        posy+=py;
        }

    void personaje::sumarframe(){
        frame++;
        }

    void personaje::setposicionsprite(Vector2f pos){
        (sprite.setPosition(pos));
        }

    void personaje::setsubrectsprite(int x1,int y1,int x2,int y2){
        sprite.setTextureRect(IntRect(Vector2i(x1,y1),Vector2i(x2,y2)));
        }
    
    void personaje::setYaActuo(bool valor) {
        yaActuo = valor;
    }

    void personaje::setTipo(TIPO_PERSONAJE nuevoTipo) {
        tipo = nuevoTipo;
    }



  void personaje::setsprite(){

          if (!textura.loadFromFile("imagen/character-spritesheet.png")) {
            std::cerr << "Error al cargar textura\n";
        }
        sprite.setTexture(textura);
        sprite.setPosition(sf::Vector2f(posx,posy));
        sprite.setTextureRect(sf::IntRect(
        sf::Vector2i(ladoCelda*0, ladoCelda*0),      // posición inicial dentro del spritesheet---Vector2i:pertenece a la libreria de SFLM y contiene 2 vectores
        sf::Vector2i(ladoCelda, ladoCelda)         // tamaño del recorte
    ));

  }
