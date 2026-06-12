#include "ia.h"
#include <cmath>

IA::IA(){

}

void IA::registrarPNJ(personaje& pers, TIPO_PERSONAJE tipo, int x, int y)
{
    int px = x * pers.getladocelda();
    int py = y * pers.getladocelda();

    pers.setposx(px);
    pers.setposy(py);
    pers.setposicionsprite(sf::Vector2f(px, py));

    pers.setdireccion(ABAJO);
    pers.setaccion(0);
    pers.setframe(0);


    // recorte inicial visible
    pers.setsubrectsprite(
        0,
        0,
        pers.getladocelda(),
        pers.getladocelda()
    );
}

/*void IA::registrarEnemigos(std::vector<personaje>* lista)
{
}*/

/*personaje* IA::detectarEnemigoCercano(personaje* p)
{
}*/

/*void IA::colocarPNJEnMapa(personaje* p, int x, int y)
{
}*/

