#ifndef JUEGO_H
#define JUEGO_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <string>
#include "grilla.h"
#include "sismov.h"
#include "personaje.h"
#include "render_interfaz_mapa.h"
#include "menu.h"
#include "managerpersonaje.h"
#include "constantes.h"
#include "cursor.h"
#include "partida.h"

class Juego {
public:
    Juego();
    void ejecutar();

private:
    void procesarEventos();
    void actualizar();
    void renderizar();

    int cargarMapa(const char* nomArch);
    int cargarTexturasDeCeldas();
    void drawAt(sf::RectangleShape &sq, float x, float y);
    void drawMovRango(sf::RectangleShape &sq, const bool *visitadas);
    void movRango(int x, int y, int mov, bool *visitadas);

    // Atributos
    sf::RenderWindow window;
    Menu menuPrincipal;
    bool enMenu;

    // Recursos
    sf::Texture texCelda[10];

    // Variables de lógica usando las clases de lucas.
    CursorJuego cursor;       // <-- Reemplaza a 'int x' e 'int y'
    Partida partida;     // <-- Gestión de turnos.
    int mov;
    sf::RectangleShape square;

    // Sistemas del juego
    Grilla tablero;
    RenderInterfazMapa rendUi;
    managerpersonaje manager;
    std::vector<personaje> pers;
    SisMov movimiento;
};

#endif // JUEGO_H
