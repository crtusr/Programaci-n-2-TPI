#ifndef CLASETRABAJO_H
#define CLASETRABAJO_H

class claseTrabajo {
protected:
    int hp;
    int maxHp;
    int fuerza;
    int defensa;

public:
    claseTrabajo();

    int getHp(); 
    int getMaxHp(); 
    int getFuerza();
    int getDefensa(); 
};

#endif
