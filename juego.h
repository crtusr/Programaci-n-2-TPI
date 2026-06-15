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
#include "texmanager.h"
#include "animacion.h"

class Juego {
public:
    Juego();
    void ejecutar();

private:
    ESTADO_JUEGO Estado;
    personaje* personajeSeleccionado;
    personaje* personajeTemporal;

    personaje* GetPersonajeSeleccionado();
    void agregarPersonaje(TIPO_PERSONAJE tipo, int x, int y);
    void moverPersonajeSeleccionado();
    bool todasLasUnidadesActuaron();
    void resetearAccionesJugador();

    void procesarEventos();
    void actualizar();
    void renderizar();

    int cargarMapa(const char* nomArch);

    // Atributos
    sf::RenderWindow window;
    Menu menuPrincipal;
    Menu* menuAccion = nullptr;
    bool enMenu;
    int teclaPresionada;
    // Recursos
    //sf::Texture texPers[10];
    // Variables de l�gica usando las clases de lucas.
    CursorJuego cursor;       // <-- Reemplaza a 'int x' e 'int y'
    Partida partida;     // <-- Gesti�n de turnos.
    int mov;
    ProcInput procesar;
    // Sistemas del juego
    TexManager texturas;
    Grilla tablero;
    RenderInterfazMapa rendUi;
    managerpersonaje manager;
    std::vector<personaje> pers;
    SisMov movimiento;
    ataque ataque;
    Animacion animacion;
    //int fase=5;//<-------por ajustar
    int cont=0;//<-----posiblemente temporal
};

#endif // JUEGO_H
