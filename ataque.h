#ifndef ATAQUE_H_INCLUDED
#define ATAQUE_H_INCLUDED
#include "personaje.h"
#include "managerpersonaje.h"
#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;
using namespace sf;

class Ataque {
private:
    int posx = 0;
    int posy = 0;
    int frame = 0;
    int opc=1;
    int impactos[6];
    int cantidadimpactos = 0;
    int daniosimpactos[6];
    int distancia = 0;
    int tipodeataque;


    Sprite sprite;
    Sprite sprite2;
    Sprite sprite3;
    Sprite sprite4;

    sf::Texture textura;

public:
    // Constructor
    Ataque() : sprite(textura),sprite2(textura),sprite3(textura),sprite4(textura)
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
        sprite3.setTexture(textura);
        sprite4.setTexture(textura);
        sprite.setPosition(sf::Vector2f(posx,posy));
        sprite2.setPosition(sf::Vector2f(posx,posy));
        sprite3.setPosition(sf::Vector2f(posx,posy));
        sprite4.setPosition(sf::Vector2f(posx,posy));


        sprite.setTextureRect(sf::IntRect(
            sf::Vector2i(64*0,64*0),      // posición inicial dentro del spritesheet---Vector2i:pertenece a la libreria de SFLM y contiene 2 vectores
            sf::Vector2i(64, 64)));        // tamaño del recorte

        sprite2.setTextureRect(sf::IntRect(
            sf::Vector2i(64*1,64*0),
            sf::Vector2i(64, 64)));

        sprite3.setTextureRect(sf::IntRect(
            sf::Vector2i(64*2,64*0),
            sf::Vector2i(64, 64)));

        sprite4.setTextureRect(sf::IntRect(
            sf::Vector2i(64*3,64*0),
            sf::Vector2i(64, 64)));
    }

    // Getters
    Sprite getsprite();

    int* getimpactos();
    int* getdaniosimpactos();
    int getcantidadimpactos();
    int getimpacto(int pos);
    int getdanio(int pos);
    int getdistancia();
    int gettipodeataque();
    string getnombreataque(int nom);
    int getopciondeataque();

void ataque1(int direccion,RenderWindow& window,vector<personaje>& pers_atk,vector<personaje>& pers_def,managerpersonaje& manager);
void ataque2(int direccion,RenderWindow& window,vector<personaje>& pers_atk,vector<personaje>& pers_def,managerpersonaje& manager);
void ataque3(int direccion,RenderWindow& window,vector<personaje>& pers_atk,vector<personaje>& pers_def,managerpersonaje& manager);
void ataque4(int direccion,RenderWindow& window,vector<personaje>& pers_atk,vector<personaje>& pers_def,managerpersonaje& manager);
void curacion1(int direccion,RenderWindow& window,vector<personaje>& pers_atk,vector<personaje>& pers_def,managerpersonaje& manager);
void prepararataque(int direccion,RenderWindow& window,vector<personaje>& pers_atk,vector<personaje>& pers_def,managerpersonaje& manager,int opc_atk);
};
#endif // ATAQUE_H_INCLUDED
