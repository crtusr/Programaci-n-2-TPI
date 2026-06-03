#ifndef COMBATE_H
#define COMBATE_H

#include "personaje.h"
#include "celda.h"

class Combate
{
  private:
    personaje *atacante;
    personaje *defendiente;
    Celda *celdaAtac;
    Celda *celdaDef;
  public:
    Combate(Grilla *g, personaje *at, personaje *def);
    void pelea();
};

#endif
