#ifndef CLASETRABAJO_H
#define CLASETRABAJO_H

class claseTrabajo {
protected:
    int hp;
    int maxHp;
    int fuerza;
    int defensa;
    int mov;

public:
    claseTrabajo();

    int getHp(); 
    int getMaxHp(); 
    int getFuerza();
    int getDefensa(); 
    int getMov();
};

#endif
