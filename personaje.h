#ifndef PERSONAJE_H_INCLUDED
#define PERSONAJE_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include <string>
#include "grilla.h"
#include "celda.h"
#include "constantes.h"
using namespace std;
using namespace sf;

class personaje {
private:
  bool yaActuo;
  int id; // Agregar un identificador único para cada personaje
    TIPO_PERSONAJE tipoPJ; // Agregar un atributo para el tipo de personaje (jugador o no jugador)
  int posx;
  int posy;
  int direccion = 0;
  int accion = 0;
  bool blokaccion = false;
  int frame = 0;
  int ladoCelda;
  /*
   *  una forma sería definir que una unidad activa
   *  es aquella que tiene un hp mayor a 0
   */
  int hp;
  int fuerza;
  int defensa;
  int maxHp;
  Grilla *grilla;
  Sprite sprite;

  sf::Texture textura;

public:
    // Constructor
    personaje(Grilla *g, int idPersonaje, TIPO_PERSONAJE tipoPersonaje) : sprite(textura)
    {
    yaActuo = false;
      fuerza = 0;
      defensa = 0;
      maxHp = 0;
      hp = 0;
      grilla = g;
      ladoCelda = g->getTamCeldaPixeles();
      id = idPersonaje;
      tipoPJ = tipoPersonaje; // Inicializar el tipo de personaje con el valor pasado al constructor
      if (!textura.loadFromFile("imagen/character-spritesheet.png")) {
          std::cerr << "Error al cargar textura\n";
      }
      posx=ladoCelda*5;
      posy=ladoCelda*5;
      sprite.setTexture(textura);
      sprite.setPosition(sf::Vector2f(posx,posy));
      sprite.setTextureRect(sf::IntRect(
        sf::Vector2i(ladoCelda*0, ladoCelda*0),      // posición inicial dentro del spritesheet---Vector2i:pertenece a la libreria de SFLM y contiene 2 vectores
        sf::Vector2i(ladoCelda, ladoCelda)         // tamaño del recorte
    ));

    }
  

    // Getters
    int getHp();
    int getFuerza();
    int getDefensa();
    int getMaxHp(); 
    int getId(); // Getter para el identificador único
    TIPO_PERSONAJE getTipo(); // Getter para el tipo de personaje
    bool getYaActuo(); // Getter para el estado de acción del personaje
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

    void setHp(int h);
    void setFuerza(int f);
    void setDef(int def);
    void setMaxHp(int mH);
    void setId(int nuevoId); // Setter para el identificador único
    void setaccion(int acc);
    void setdireccion(int drc);
    void setframe(int fra);
    void setblockaccion(bool block);
    void setposx(int px);
    void setposy(int py);
    void setsumresposx(int px);
    void setsumresposy(int py);
    void sumarframe();
    void setSprite(sf::Texture &tex);
    void setposicionsprite(Vector2f pos);
    void setsubrectsprite(int x1,int y1,int x2,int y2);
    void setTipo(TIPO_PERSONAJE nuevoTipo); // Setter para el tipo de personaje
    void setYaActuo(bool valor); // Setter para el estado de acción del personaje
    void setsprite(sf::Texture &tex);
    /*void setsprite(int tipo);*/
    bool restarHp(int num);
};
#endif // PERSONAJE_H_INCLUDED
