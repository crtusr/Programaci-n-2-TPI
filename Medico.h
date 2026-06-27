#ifndef MEDICO_H
#define MEDICO_H

#include "claseTrabajo.h"

class Medico : public claseTrabajo {
public:
    Medico() {
        fuerza = 4;
        defensa = 2;
        maxHp = 35;
        hp = 35;
        mov = 4;
        optAtk[0] = CURA;
        optAtk[1] = GRANADA;
    }
};

#endif

