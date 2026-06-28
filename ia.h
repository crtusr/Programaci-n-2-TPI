#ifndef IA_H_INCLUDED
#define IA_H_INCLUDED
#include "personaje.h"
#include "grilla.h"
#include "managerpersonaje.h"
#include "sismov.h"
#include <vector>


class IA
{
private:
    Grilla* tablero;
    personaje *personajeIA;
    managerpersonaje* manager;
    int contIA;
public:
    IA(Grilla *t, managerpersonaje *p);

    void registrarPNJ(personaje& pers, TIPO_PERSONAJE tipo, int x, int y);

    std::pair<int, int> detectarEnemigoCercano(std::vector<personaje>& aliados, std::vector<personaje>& enemigos);
    std::pair<int, int> casillaValida(int pj, std::vector<personaje>& aliados, std::vector<personaje>& enemigos,SisMov& movimiento);
    std::pair<int, int> acercarceAlEnemigo(int pj,std::vector<personaje>& aliados, std::vector<personaje>& enemigos);

    int getContIA();
    void inContIA();
    void resetContIA();
    /*void moverseAlEnemigo(personaje& enemigo);*/
};

#endif // IA_H_INCLUDED