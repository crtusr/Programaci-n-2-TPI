#include "ia.h"
#include <cmath>


IA::IA(){
int cont = 0;
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
    for (int i = 0; i <enemigos.size(); i++)
    {
        if(!enemigos[i].getYaActuo())
        {
            for (int j = 0; j < aliados.size(); j++)
            {
                int pasos = abs(aliados[j].getPosx() - enemigos[i].getPosx()) + abs(aliados[j].getPosy() - enemigos[i].getPosy());
                if(pasos < MenosPasos)
                {
                    MenosPasos = pasos;
                    idMasCercano = aliados[j].getId();
                }
            }
        }
    }
    cout << "pasos: " << MenosPasos <<", "<<"id: "<< idMasCercano << endl;
    if(MenosPasos == 999)
    {
        return -1;
    }
    else
    {
        return MenosPasos;
    }
}


