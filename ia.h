#ifndef IA_H_INCLUDED
#define IA_H_INCLUDED
#include "personaje.h"
#include "grilla.h"
#include <vector>


class IA
{
private:
    std::vector<personaje*> vectorPJ;   // PNJ registrados
    std::vector<personaje*> vectorPNJ; // Referencia a personajes del jugador
    Grilla* tablero;
    personaje *personajeIA;

public:
    IA();

    void registrarPNJ(personaje& pers, TIPO_PERSONAJE tipo, int x, int y);
    void registrarEnemigos(std::vector<personaje>* lista);

    personaje* detectarEnemigoCercano(personaje* p);
    void colocarPNJEnMapa(personaje* p, int x, int y);
};

#endif // IA_H_INCLUDED