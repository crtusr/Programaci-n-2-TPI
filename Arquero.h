#ifndef ARQUERO_H
#define ARQUERO_H

#include "claseTrabajo.h"

class Arquero : public claseTrabajo {
  public:
    Arquero() {
        fuerza = 9;
        defensa = 1;
        maxHp = 28;
        hp = 28;
        mov = 5;
        optAtk[0] = PROYECTIL;
        optAtk[1] = GRANADA;
    }
};

#endif

