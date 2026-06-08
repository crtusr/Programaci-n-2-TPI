#ifndef IA_H_INCLUDED
#define IA_H_INCLUDED
#include "personaje.h"
#include "grilla.h"
#include <vector>


class IA {
private:
    personaje *personajeIA;

    std::vector<personaje*> vectorPNJ ; // Vector que contiene todos los personajes no jugadores (PNJ) en el juego
    std::vector<personaje*> vectorPJ ; // Vector que contiene todos los personajes jugadores en el juego
public:
    IA(personaje *p, Grilla *g);

    personaje* getPersonajeIA(personaje *p);

    personaje* buscarEnemigoMasCercano();
    personaje* buscarAliadoMasCercano();

    void setPersonajeIA(personaje *p);
    void moverEnemigo();
    void moverAliado();
    void atacarEnemigo();

// Funciones para agregar personajes a los vectores correspondientes
    void agregrarPNJ(personaje *p);
    void agregarPJ(personaje *p);
};

#endif // IA_H_INCLUDED