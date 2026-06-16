#ifndef ARQUERO_H
#define ARQUERO_H

#include "claseTrabajo.h"

class Arquero : public claseTrabajo {
public:
    Arquero() {
        fuerza = 9;
        defensa = 3;
        maxHp = 28;
        hp = 28;
    }
};

#endif

