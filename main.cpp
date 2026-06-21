#include <string>
#include "managerjuego.h"

int main() {
    ManagerJuego miManager;
    bool salir = false;

    while(!salir)
    {
        salir = miManager.mostrarMenuPrincipal();
        if(salir) break;

        int cantidadDeNiveles = 1;
        bool jugadorSigueVivo = true;

        for(int i = 1; i <= cantidadDeNiveles; i++)
        {
            std::string archivoMapa = "nivel" + std::to_string(i) + ".txt";
            std::string archivoPers = "personajes" + std::to_string(i) + ".txt";

            jugadorSigueVivo = miManager.cargarPartida(archivoMapa.c_str(), archivoPers.c_str());

            if(!jugadorSigueVivo) break;
        }
    }
    return 0;
}
