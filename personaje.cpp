#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include "personaje.h"

using namespace std;
using namespace sf;



/* ============================
        GETTERS
   ============================ */
// personaje.cpp


int personaje::getId() { return id; }

int personaje::getPosx() { return posx / ladoCelda; }
int personaje::getPosy() { return posy / ladoCelda; }

int personaje::getPosxPxl() { return posx; }
int personaje::getPosyPxl() { return posy; }

int personaje::getHp() { return hp; }
int personaje::getFuerza() { return fuerza; }
int personaje::getDefensa() { return defensa; }
int personaje::getMaxHp() { return maxHp; }

int personaje::getHpReal()
{
  return hp + trabajo->getMaxHp();
}
int personaje::getFuerzaReal()
{
  return fuerza + trabajo->getFuerza();
}
int personaje::getDefensaReal()
{
  return defensa + trabajo->getDefensa();
}
int personaje::getMaxHpReal()
{
  return maxHp + trabajo->getMaxHp();
}
int personaje::getMovReal()
{
  return mov + trabajo->getMov();
}


int personaje::getdireccion() { return direccion; }
int personaje::getaccion() { return accion; }
bool personaje::getblockaccion() { return blokaccion; }
int personaje::getframe() { return frame; }
int personaje::getladocelda() { return ladoCelda; }

bool personaje::getYaActuo() { return yaActuo; }
TIPO_PERSONAJE personaje::getTipo() { return tipoPJ; }


Sprite personaje::getsprite() { return sprite; }
void personaje::setSprite(sf::Texture &tex)
{
  sprite.setTexture(tex);
}

Vector2f personaje::getPosicionF() { return Vector2f(posx, posy); }
Vector2i personaje::getPosicionI() { return Vector2i(posx, posy); }


/* ============================
        SETTERS
   ============================ */

void personaje::setId(int nuevoId) { id = nuevoId; }

void personaje::setHp(int h) { hp = h; }
void personaje::setFuerza(int f) { fuerza = f; }
void personaje::setDef(int def) { defensa = def; }
void personaje::setMaxHp(int mH) { maxHp = mH; }

void personaje::setTrabajo(claseTrabajo *t)
{
  trabajo = t;
}

void personaje::setaccion(int acc) { accion = acc; }
void personaje::setdireccion(int drc) { direccion = drc; }
void personaje::setframe(int fra) { frame = fra; }
void personaje::setblockaccion(bool block) { blokaccion = block; }

void personaje::setposx(int px) { posx = px; }
void personaje::setposy(int py) { posy = py; }

void personaje::setsumresposx(int px) { posx += px; }
void personaje::setsumresposy(int py) { posy += py; }

void personaje::sumarframe() { frame++; }

void personaje::setposicionsprite(Vector2f pos) { sprite.setPosition(pos); }

void personaje::setsubrectsprite(int x1, int y1, int x2, int y2) {
    sprite.setTextureRect(IntRect(Vector2i(x1, y1), Vector2i(x2, y2)));
}

void personaje::setYaActuo(bool valor) { yaActuo = valor; }

void personaje::setTipo(TIPO_PERSONAJE nuevoTipo) { tipoPJ = nuevoTipo; }


/* ============================
        SPRITE
   ============================ */

void personaje::setsprite(sf::Texture &tex)
{
    sprite.setTexture(tex);
    sprite.setTextureRect(sf::IntRect(
        sf::Vector2i(0, 0),
        sf::Vector2i(ladoCelda, ladoCelda)
    ));
    sprite.setPosition(sf::Vector2f(posx, posy));
}

/*  void personaje::setsprite(int tipo){
switch(tipo){
case 1:
    if (!textura.loadFromFile("imagen/character-spritesheet.png")) {
            std::cerr << "Error al cargar textura\n";
        }
    break;
case 2:break;
case 3:break;
case 4:break;
case 5:break;
default:break;

}*/


/* ============================
        LÓGICA
   ============================ */



void personaje::sumarHP(int num)
{
  if(num <= 0)
    return;
  hp += num;
  if(hp > maxHp)
    hp = maxHp;
}

/*IMPORTANTE: cuando se agreguen los trabajos se deberían acceder como hp*/

bool personaje::restarHp(int num)
{
    if(num <= 0)
      return false;
    hp -= num;

    if (hp + trabajo->getMaxHp() <= 0) {
        hp = -trabajo->getMaxHp();
        return true;   // murió
    }

    return false;       // sigue vivo
}
