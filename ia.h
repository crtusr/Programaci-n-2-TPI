#ifndef IA_H_INCLUDED
#define IA_H_INCLUDED
#include "personaje.h"
#include "grilla.h"

class IA {
private:
    personaje *personajeIA;
public:
    IA(personaje *p, Grilla *g);
    personaje* getPersonajeIA();
    personaje* buscarEnemigoMasCercano();
    personaje* buscarAliadoMasCercano();
    void setPersonajeIA(personaje *p);
    void moverEnemigo();
    void moverAliado();
    void atacarEnemigo();
};

#endif // IA_H_INCLUDED