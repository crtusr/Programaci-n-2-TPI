#ifndef MANAGERJUEGO_H
#define MANAGERJUEGO_H

#include <SFML/Graphics.hpp>
#include "menu.h" //

class ManagerJuego {
private:
    sf::RenderWindow window;
    Menu menuInicio; //

public:
    ManagerJuego();
    bool mostrarMenuPrincipal();
    bool cargarPartida(const char* archivoMapa, const char* archivoPersonajes);
};

#endif
