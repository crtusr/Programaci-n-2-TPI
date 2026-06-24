#ifndef ANIMACION_H_INCLUDED
#define ANIMACION_H_INCLUDED
#include <SFML/Graphics.hpp>
#include "personaje.h"
#include "ataque.h"

using namespace std;
using namespace sf;

class Animacion{

private:
int anim_frame = 0;
bool anim_activa[6] = {};
int v_posx[6];
int v_posy[6];
int danios[6];
Sprite sprite;
Texture textura;
Font font;
Text text;

public:
        Animacion() : sprite(textura),text(font," ",20)
    {
        if (!textura.loadFromFile("imagen/Sprite-000_gplpe1.png")) {
            std::cerr << "Error al cargar textura\n";
        }
            if (!font.openFromFile("assets/Roboto-VariableFont_wdth,wght.ttf")) {
            std::cerr << "Error al cargar fuente\n";
        }
    sprite.setTexture(textura);
    sprite.setPosition(sf::Vector2f(0,0));
    sprite.setTextureRect(sf::IntRect(
        sf::Vector2i(64*0,64*0),      // posici�n inicial dentro del spritesheet---Vector2i:pertenece a la libreria de SFLM y contiene 2 vectores
        sf::Vector2i(64, 64)         // tama�o del recorte
    ));
    }
void asignaranimacion(vector<personaje>& pers_atk,vector<personaje>& pers_def,Ataque& ataque,managerpersonaje& manager);
void mostraranimacion(RenderWindow& window);
void mostrarvida(RenderWindow& window,vector<personaje>& pers);
};

#endif // ANIMACION_H_INCLUDED;
