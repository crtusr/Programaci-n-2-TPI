#include "ia.h"
#include <cmath>


IA::IA(){
contIA = 0;
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
    int intentos = 0;
    while(enemigos[contIA].getYaActuo())
    {
        contIA++;
        if(contIA >= enemigos.size()){contIA = 0;}

        intentos++;
        if(intentos>= enemigos.size()){return -1;}
    }
    

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
    contIA++;
    
    return idMasCercano;
}

int IA::getContIA() { return contIA; }

void IA::resetContIA() {contIA = 0;}



