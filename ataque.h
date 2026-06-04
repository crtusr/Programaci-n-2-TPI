#ifndef ATAQUE_H_INCLUDED
#define ATAQUE_H_INCLUDED
#include "personaje.h"
#include "managerpersonaje.h"
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class ataque {
private:
    int posx = 0;
    int posy = 0;
    int frame = 0;
    int v_dirx[10] = {};
    int v_diry[10] = {};
    int opc=1;

    Sprite sprite;

    sf::Texture textura;

public:
    // Constructor
    ataque() : sprite(textura)
    {
        if (!textura.loadFromFile("imagen/Sprite-preparado1-Sheet.png")) {
            std::cerr << "Error al cargar textura\n";
        }
        posx=0;
        posy=0;
        sprite.setTexture(textura);
    sprite.setPosition(sf::Vector2f(posx,posy));


    sprite.setTextureRect(sf::IntRect(
        sf::Vector2i(0, 0),      // posición inicial dentro del spritesheet---Vector2i:pertenece a la libreria de SFLM y contiene 2 vectores
        sf::Vector2i(64, 64)         // tamaño del recorte
    ));

    }


    // Getters
    Sprite getsprite();

void ataque1(int posx,int posy,int direccion,RenderWindow& window);
void ataque2(int posx,int posy,int direccion,RenderWindow& window);
void ataque3();
void ataque4();
void prepararataque(int posx,int posy,int direccion,RenderWindow& window);
};
#endif // ATAQUE_H_INCLUDED
