#ifndef IA_H_INCLUDED
#define IA_H_INCLUDED
#include "personaje.h"
#include "grilla.h"
#include "managerpersonaje.h"
#include "sismov.h"
#include <vector>


class IA
{
private:
    Grilla* tablero;
    personaje *personajeIA;
    int contIA;
public:
    IA();

    void registrarPNJ(personaje& pers, TIPO_PERSONAJE tipo, int x, int y);

    int detectarEnemigoCercano(std::vector<personaje>& aliados, std::vector<personaje>& enemigos);

    int getContIA();
    void resetContIA();
    /*void moverseAlEnemigo(personaje& enemigo);*/
};

#endif // IA_H_INCLUDED