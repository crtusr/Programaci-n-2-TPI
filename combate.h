#ifndef COMBATE_H
#define COMBATE_H

#include "personaje.h"
#include "celdaterrestre.h"

class Combate
{
  private:
    personaje *atacante;
    personaje *defendiente;
    //puse CeldaTerrestre para tener el metodo get defensa pero estoy abierto a opciones
    CeldaTerrestre *celdaAtac;
    CeldaTerrestre *celdaDef;
  public:
    Combate(Grilla *g, personaje *at, personaje *def);
    void curacion();
    void pelea();
};

#endif
