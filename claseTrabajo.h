#ifndef CLASETRABAJO_H
#define CLASETRABAJO_H

class claseTrabajo {
protected:
    int idTrabajo; // NUEVO: Identificador de la clase.
    int hp;
    int maxHp;
    int fuerza;
    int defensa;
    int mov;

public:
    claseTrabajo();

    int getIdTrabajo(); // NUEVO: Para saber qué menú mostrar.
    void setIdTrabajo(int id); // NUEVO: Para asignarlo al crearlo.

    int getHp();
    int getMaxHp();
    int getFuerza();
    int getDefensa();
    int getMov();
};

#endif
