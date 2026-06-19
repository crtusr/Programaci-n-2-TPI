#ifndef GUERRERO_H
#define GUERRERO_H

#include "claseTrabajo.h"

class Guerrero : public claseTrabajo {
public:
    Guerrero() {
        fuerza = 12;
        defensa = 8;
        maxHp = 40;
        hp = 40;
    }
};

#endif

