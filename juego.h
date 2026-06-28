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
#include "ia.h"
#include "texmanager.h"
#include "animacion.h"
#include "adminclase.h"
#include "adminmusica.h"

class Juego {
public:
    // El constructor ahora recibe los archivos de texto
    Juego(const char* archivoMapa, const char* archivoPersonajes);

    // Ejecutar devuelve un bool para avisarle al manager si ganó o salió, y recibe la ventana
    bool ejecutar(sf::RenderWindow& window);

private:
    ESTADO_JUEGO Estado;
    ESTADO_IA EstadoIA;
    personaje* personajeSeleccionado;
    personaje* personajeTemporal;
    AdminMusica musica;
    // Banderas para controlar el flujo del nivel
    bool nivelSuperado;
    bool jugadorQuiereSalir;

    personaje* GetPersonajeSeleccionado();
    void SpawnPersonaje(const char* archivoPersonajes); // Recibe el txt
    void agregarPersonaje(TIPO_PERSONAJE tipo, int x, int y);
    void agregarPersonajeNJ(TIPO_PERSONAJE tipo, int x, int y);
    bool todasLasUnidadesActuaron(std::vector<personaje>& faccion);
    void resetearAccionesJugador(std::vector<personaje>& faccion);
    void procesarIA(sf::RenderWindow &window);

    // Estas funciones ahora necesitan la ventana prestada
    void procesarEventos(sf::RenderWindow& window);
    void actualizar();
    void renderizar(sf::RenderWindow& window);

    int cargarMapa(const char* nomArch);
    void declararCuracion(vector<personaje>& propio, personaje *actual);
    void declararAtaque(vector<personaje>& atk,vector<personaje>& def, personaje *actual);
    // Atributos de UI In-game
    Menu* menuAccion;
    Menu *menuSubOpciones;
    Menu *menuPausa;
    int teclaPresionada;

    // Recursos
    sf::Texture texCelda[10];
    //sf::Texture texPers[10];
    // Variables de l�gica usando las clases de lucas.
    CursorJuego cursor;       // <-- Reemplaza a 'int x' e 'int y'
    Partida partida;     // <-- Gesti�n de turnos.
    sf::RectangleShape square;
    ProcInput procesar;

    // Sistemas del juego
    TexManager texturas;
    AdminClase trabajos;
    Grilla tablero;
    RenderInterfazMapa rendUi;
    managerpersonaje manager;
    IA ia;
    std::vector<personaje> pers;
    std::vector<personaje> persNJ;
    SisMov movimiento;
    Ataque ataque;
    Animacion animacion;
    int cont = 0;
    int idIA = 0;
};

#endif // JUEGO_H
