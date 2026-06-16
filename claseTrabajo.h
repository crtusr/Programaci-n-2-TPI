#ifndef CLASETRABAJO_H
#define CLASETRABAJO_H

class claseTrabajo {
protected:
    int hp;
    int maxHp;
    int fuerza;
    int defensa;

public:
    claseTrabajo() : hp(0), maxHp(0), fuerza(0), defensa(0) {}

    int getHp() { return hp; }
    int getMaxHp() { return maxHp; }
    int getFuerza() { return fuerza; }
    int getDefensa() { return defensa; }
};

#endif
