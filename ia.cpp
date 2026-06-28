#include "ia.h"
#include <cmath>


IA::IA(Grilla *t, managerpersonaje *p){
contIA = 0;
tablero = t;
manager = p;
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

std::pair<int, int> IA::detectarEnemigoCercano(std::vector<personaje>& aliados, std::vector<personaje>& enemigos)
{
    int persMasCercano[2] = {-1, 999};

            for (int i = 0; i < aliados.size(); i++)
            {
                if(aliados[i].getHpReal() == 0)
                  continue;
                int pasos = abs(aliados[i].getPosx() - enemigos[contIA].getPosx()) + abs(aliados[i].getPosy() - enemigos[contIA].getPosy());
                if(pasos < persMasCercano[1])
                {
                    persMasCercano[1] = pasos;
                    persMasCercano[0] = aliados[i].getId();
                }
            }
        
    cout << "pasos: " << persMasCercano[1] <<", "<<"id: "<< persMasCercano[0] << endl;
    return std::make_pair(persMasCercano[0], persMasCercano[1]);
}

std::pair<int, int> IA::casillaValida(int pj, std::vector<personaje>& aliados, std::vector<personaje>& enemigos, SisMov& movimiento)
{
    int dirX[4] = { 0, 0, -1, 1 };
    int dirY[4] = { -1, 1, 0, 0 };
    int casillaValida[2] = {-1, -1}; 

    int menosPasos = 999;
    for (int i = 0; i < 4; i++) 
    {
        int x = aliados[pj].getPosx() + dirX[i];
        int y = aliados[pj].getPosy() + dirY[i];

            if (x < 0 || x >= tablero->getMaxX() || y < 0 || y >= tablero->getMaxY())  
            {
                continue; // Salta a la siguiente iteración
            }

            bool ocupada = false;

            for (int j = 0; j < aliados.size(); j++) 
            {
                if (aliados[j].getPosx() == x && aliados[j].getPosy() == y) 
                {
                    ocupada = true;
                    break;
                }
            }

            if (!ocupada) {
            for (int k = 0; k < enemigos.size(); k++) 
            {
                if (enemigos[k].getPosx() == x && enemigos[k].getPosy() == y) 
                {
                    ocupada = true;
                    break;
                }
            }
        

            if (ocupada == false) 
            {
                int pasos = std::abs(x - enemigos[contIA].getPosx()) + std::abs(y - enemigos[contIA].getPosy());
            
                if (pasos < menosPasos && movimiento.Alcanzable(x, y)) 
                {
                    menosPasos = pasos;
                    casillaValida[0] = x;
                    casillaValida[1] = y;
                }
            }

        }
    }

    return std::make_pair (casillaValida[0], casillaValida[1]);
}

std::pair<int, int> IA::acercarceAlEnemigo(int pj,std::vector<personaje>& aliados, std::vector<personaje>& enemigos, SisMov& movimiento)
{
    int pasos = abs(aliados[pj].getPosx() - enemigos[contIA].getPosx()) + abs(aliados[pj].getPosy() - enemigos[contIA].getPosy());

        int coordenadaX = aliados[pj].getPosx();
        int coordenadaY = aliados[pj].getPosy();

    while (pasos > 1)
    {
        int pasosDisp = enemigos[contIA].getMovReal();
        int nuevoX = enemigos[contIA].getPosx();
        int nuevoY = enemigos[contIA].getPosy();

    while (pasosDisp > 0)
    {
        if (nuevoX != coordenadaX) 
        {
            nuevoX += (coordenadaX > nuevoX) ? 1 : -1;
            pasosDisp--;
        }
        // Luego movimiento en Y
        if (pasosDisp > 0 && nuevoY != coordenadaY) 
        {
            nuevoY += (coordenadaY > nuevoY) ? 1 : -1;
            pasosDisp--;
        }
    }

    while (managerpersonaje::comprobarLugarTablero(nuevoX, nuevoY, aliados) != -1 ||managerpersonaje::comprobarLugarTablero(nuevoX, nuevoY, enemigos) != -1)
    {

        if (nuevoX != enemigos[contIA].getPosx()) nuevoX += (enemigos[contIA].getPosx() > nuevoX) ? 1 : -1;
        else if (nuevoY != enemigos[contIA].getPosy()) nuevoY += (enemigos[contIA].getPosy() > nuevoY) ? 1 : -1;
        

        if (nuevoX == enemigos[contIA].getPosx() && nuevoY == enemigos[contIA].getPosy()) break; 
    }

    return {nuevoX, nuevoY};
    }
}


int IA::getContIA() { return contIA; }

void IA::inContIA() {contIA++;}
void IA::resetContIA() {contIA = 0;}



