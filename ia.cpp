#include "ia.h"
#include <cmath>


IA::IA(Grilla *t){
contIA = 0;
tablero = t;
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

int IA::detectarEnemigoCercano(std::vector<personaje>& aliados, std::vector<personaje>& enemigos)
{

    int MenosPasos = 999;
    int idMasCercano;

            for (int i = 0; i < aliados.size(); i++)
            {
                int pasos = abs(aliados[i].getPosx() - enemigos[contIA].getPosx()) + abs(aliados[i].getPosy() - enemigos[contIA].getPosy());
                if(pasos < MenosPasos)
                {
                    MenosPasos = pasos;
                    idMasCercano = aliados[i].getId();
                }
            }
        
    cout << "pasos: " << MenosPasos <<", "<<"id: "<< idMasCercano << endl;
    return idMasCercano;
}

std::pair<int, int> IA::casillaValida(int pj, std::vector<personaje>& aliados, std::vector<personaje>& enemigos)
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
            
                if (pasos < menosPasos) 
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



int IA::getContIA() { return contIA; }

void IA::inContIA() {contIA++;}
void IA::resetContIA() {contIA = 0;}



