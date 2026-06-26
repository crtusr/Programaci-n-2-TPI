#ifndef ANIMACION_H_INCLUDED
#define ANIMACION_H_INCLUDED
#include <SFML/Graphics.hpp>
#include "personaje.h"
#include "ataque.h"

using namespace std;
using namespace sf;

class Animacion{

private:
int aux_x=0;
int aux_y=0;
int atk_frame = 0;
bool atk_activo = false;
int anim_frame = 0;
bool anim_activa[6] = {};
int v_posx[6];
int v_posy[6];
int danios[6];
Sprite sprite;
Texture textura;
Font font;
Text text;
int tipodeataque;

// Declaracion de variables nuevas
Texture tex_ataque2;
    Sprite spt_ataque2;

    Texture tex_ataque3;
    Sprite spt_ataque3;

    Texture tex_ataque4;
    Sprite spt_ataque4;

    Texture tex_curacion1;
    Sprite spt_curacion1;

public:
        Animacion() : sprite(textura),text(font," ",20),spt_ataque2(tex_ataque2),spt_ataque3(tex_ataque3),spt_ataque4(tex_ataque4),spt_curacion1(tex_curacion1)
    {
        if (!textura.loadFromFile("imagen/sprite_impactos.png")) {
            std::cerr << "Error al cargar textura\n";
        }
                if (!tex_ataque2.loadFromFile("imagen/sprite-atk2.png")) {
            std::cerr << "Error al cargar textura\n";
        }
                if (!tex_ataque3.loadFromFile("imagen/sprite_bomba_1-sheet.png")) {
            std::cerr << "Error al cargar textura\n";
        }
                if (!tex_ataque4.loadFromFile("imagen/flecha.png")) {
            std::cerr << "Error al cargar textura\n";
        }
                if (!tex_curacion1.loadFromFile("imagen/sprite_bomba_heler_.png")) {
            std::cerr << "Error al cargar textura\n";
        }
            if (!font.openFromFile("assets/Roboto-VariableFont_wdth,wght.ttf")) {
            std::cerr << "Error al cargar fuente\n";
        }
    sprite.setTexture(textura);
    spt_ataque2.setTexture(tex_ataque2);
    spt_ataque3.setTexture(tex_ataque3);
    spt_ataque4.setTexture(tex_ataque4);
    spt_curacion1.setTexture(tex_curacion1);

    }
void asignaranimacion(vector<personaje>& pers_atk,vector<personaje>& pers_def,Ataque& ataque,managerpersonaje& manager);
void mostraranimacion(RenderWindow& window);
void mostrarvida(RenderWindow& window,vector<personaje>& pers);
void mostrarataque(personaje& pers,RenderWindow& window,Ataque& ataque);
};

#endif // ANIMACION_H_INCLUDED;
