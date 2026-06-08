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
    TIPO_PERSONAJE tipo; // Agregar un atributo para el tipo de personaje (jugador o no jugador)
    int posx;
    int posy;
    int direccion;
    int accion;
    bool blokaccion;
    int frame;
    int ladoCelda;
    Grilla *grilla;
    Sprite sprite;

    sf::Texture textura;

public:
    // Constructor
    personaje(Grilla *g, int idPersonaje, TIPO_PERSONAJE tipoPersonaje) : sprite(textura)
    {
        yaActuo = false;
        posx = 0;
        posy = 0;
        direccion = 0;
        accion = 0;
        blokaccion = false;
        frame = 0;
        grilla = g;
        ladoCelda = g->getTamCeldaPixeles();
        id = idPersonaje;
        tipo = tipoPersonaje; // Inicializar el tipo de personaje con el valor pasado al constructor
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
    int getId(); // Getter para el identificador único
    TIPO_PERSONAJE getTipo(); // Getter para el tipo de personaje
    int getPosx();            //posx tiene que devolver la posición en la grilla
    int getPosy();            //posx tiene que devolver la posición en la grilla
    int getPosxPxl();         // Devuelve la posición en píxeles
    int getPosyPxl();         // Devuelve la posición en píxeles
    int getdireccion();       // Devuelve la dirección actual del personaje
    int getaccion();          // Devuelve la acción actual del personaje
    bool getblockaccion();    // Devuelve si el personaje tiene bloqueada la acción
    int getframe();           // Devuelve el frame actual del personaje
    int getladocelda();       // Devuelve el tamaño de la celda en píxeles
    bool getYaActuo();        // Devuelve si el personaje ya actuó en el turno actual
    Sprite getsprite();       // Devuelve el sprite del personaje
    Vector2f getPosicionF();  // Devuelve la posición del personaje como un Vector2f (útil para renderizar)
    Vector2i getPosicionI();  // Devuelve la posición del personaje como un Vector2i (útil para cálculos de lógica)

// Setters
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
    void setposicionsprite(Vector2f pos);
    void setsubrectsprite(int x1,int y1,int x2,int y2);
    void setsprite();
    void setTipo(TIPO_PERSONAJE nuevoTipo); // Setter para el tipo de personaje
    void setYaActuo(bool valor); // Setter para el estado de acción del personaje
};
#endif // PERSONAJE_H_INCLUDED

