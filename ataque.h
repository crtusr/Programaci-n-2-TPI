#ifndef ATAQUE_H_INCLUDED
#define ATAQUE_H_INCLUDED
#include "personaje.h"
#include "managerpersonaje.h"
#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;
using namespace sf;

class ataque {
private:
    int posx = 0;
    int posy = 0;
    int frame = 0;
    int opc=1;
    int impactos[6];
    int cantidadimpactos = 0;
    int daniosimpactos[6];


    Sprite sprite;
    Sprite sprite2;

    sf::Texture textura;

public:
    // Constructor
    ataque() : sprite(textura),sprite2(textura)
    {
        if (!textura.loadFromFile("imagen/Sprite-preparado1-Sheet.png")) {
            std::cerr << "Error al cargar textura\n";
        }
        for(int i = 0; i < 6; i++)
        {
          impactos[i] = 0x7FFFFFFF;// no estaría mal inicializar con un valor invalido
          daniosimpactos[i] = 0;
        }
        posx=0;
        posy=0;
        sprite.setTexture(textura);
        sprite2.setTexture(textura);
        sprite.setPosition(sf::Vector2f(posx,posy));
        sprite2.setPosition(sf::Vector2f(posx,posy));


        sprite.setTextureRect(sf::IntRect(
            sf::Vector2i(64*0,64*0),      // posición inicial dentro del spritesheet---Vector2i:pertenece a la libreria de SFLM y contiene 2 vectores
            sf::Vector2i(64, 64)         // tamaño del recorte
        ));
        sprite2.setTextureRect(sf::IntRect(
            sf::Vector2i(64*1,64*0),      // posición inicial dentro del spritesheet---Vector2i:pertenece a la libreria de SFLM y contiene 2 vectores
            sf::Vector2i(64, 64)         // tamaño del recorte
        ));
    }

    // Getters
    Sprite getsprite();

    int* getimpactos();
    int* getdaniosimpactos();
    int getcantidadimpactos();

void ataque1(int direccion,RenderWindow& window,vector<personaje>& pers,managerpersonaje& manager);
void ataque2(int direccion,RenderWindow& window,vector<personaje>& pers,managerpersonaje& manager);
void ataque3();
void ataque4();
void prepararataque(int direccion,RenderWindow& window,vector<personaje>& pers,managerpersonaje& manager);
};
#endif // ATAQUE_H_INCLUDED
