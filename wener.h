#ifndef ARQUERO_H
#define ARQUERO_H

#include "claseTrabajo.h"

class Wenner : public claseTrabajo {
  public:
    Wenner() {
        fuerza = 10;
        defensa = 1;
        maxHp = 50;
        hp = 50;
        mov = 2;
        optAtk[0] = SIMPLE;
        optAtk[1] = GRANADA;
    }
};

#endif