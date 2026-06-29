#ifndef GENERICO_H
#define GENERICO_H
#include "claseTrabajo.h"

class Generico : public claseTrabajo {
  public:
    Generico() {
        fuerza = 6;
        defensa = 1;
        maxHp = 25;
        hp = 25;
        mov = 3;
        optAtk[0] = SIMPLE;
    }
};


#endif
