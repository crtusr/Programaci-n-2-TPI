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
#include "proc_input.h"
#include "ataque.h"
enum EstadoJuego{
    CursorLibre,
    PersonajeSeleccionado,
};
class Juego {
public:
    Juego();
    void ejecutar();

private:
    EstadoJuego Estado = CursorLibre;
    personaje* personajeSeleccionado = nullptr;

    personaje* GetPersonajeSeleccionado();
    void moverPersonajeSeleccionado();
    bool todasLasUnidadesActuaron();
    void resetearAccionesJugador();

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
    int teclaPresionada;
    // Recursos
    sf::Texture texCelda[10];

    // Variables de l�gica usando las clases de lucas.
    CursorJuego cursor;       // <-- Reemplaza a 'int x' e 'int y'
    Partida partida;     // <-- Gesti�n de turnos.
    int mov;
    sf::RectangleShape square;
    ProcInput procesar;
    // Sistemas del juego
    Grilla tablero;
    RenderInterfazMapa rendUi;
    managerpersonaje manager;
    std::vector<personaje> pers;
    SisMov movimiento;
    ataque ataque;
    int fase=5;//<-------por ajustar
    int cont=0;//<-----posiblemente temporal
};

#endif // JUEGO_H
