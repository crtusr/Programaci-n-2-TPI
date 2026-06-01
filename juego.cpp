#include "juego.h"
#include "defaultcelda.h"
#include "celdaterrestre.h"
#include "proc_input.h"
#include <cstdio>


// CONSTRUCTOR: Inicializa el Cursor y la Partida.
Juego::Juego() :
    window(sf::VideoMode({1024, 768}), "SFML 3"),
    menuPrincipal(1024, 768),
    enMenu(true),
    cursor(0, 0),
    partida(0, 0),
    mov(3),
    tablero(64, 11, 11),
    rendUi(&tablero),
    pers(5, personaje(&tablero)),
    movimiento(3, 3, &tablero)
{
    window.setFramerateLimit(60);

    square.setSize(sf::Vector2f(64,64));
    square.setFillColor(sf::Color(127, 127, 255, 127));
    teclaPresionada = 0;
    cargarTexturasDeCeldas();
    cargarMapa("testmap.txt");

    for(int i = 0; i < 5; i++) {
        manager.Asignarpersonajes(pers[i]);
    }
}

void Juego::ejecutar() {
    while (window.isOpen()) {
        procesarEventos();
        actualizar();
        renderizar();
    }
}

// EVENTOS: Movemos el cursor con el ENUM de constantes.h que hizo lucas.
void Juego::procesarEventos() {
    while (const std::optional<sf::Event> event = window.pollEvent()) 
    {
        if (event->is<sf::Event::Closed>()) 
        {
            window.close();
        }
        else if(const auto *resized = event->getIf<sf::Event::Resized>()) 
        {
            sf::FloatRect newSize(sf::Vector2f(0, 0), sf::Vector2f(resized->size.x, resized->size.y));
            window.setView(sf::View(newSize));
        }
        else if (const auto *key = event->getIf<sf::Event::KeyPressed>()) 
        {
            /* Pienso que habria que hacer un atributo que sea el estado del 
             * juego (en el menu, en el tablero, moviendo el personaje o 
             * seleccionado objetivo) y que se decida el comportamiento en base
             * al estado
             */
            teclaPresionada = procesar.tecla(key->code);
            if (enMenu) 
            {
                if (teclaPresionada == ARRIBA) menuPrincipal.moveUp();
                else if (teclaPresionada == ABAJO) menuPrincipal.moveDown();
                else if (teclaPresionada == ENTER) 
                {
                    int opcion = menuPrincipal.getPressedItem();
                    if (opcion == 0) enMenu = false;
                    else if (opcion == 2) window.close();
                }
            }
            else {
              // Control del movimiento usando la clase Cursor de lucas.
                if (teclaPresionada == IZQUIERDA) {
                    if (cursor.getXPos() > 0) cursor.mover(IZQUIERDA);
                }
                else if (teclaPresionada == DERECHA) {
                    if (cursor.getXPos() < 10) cursor.mover(DERECHA);
                }
                else if (teclaPresionada == ARRIBA) {
                    if (cursor.getYPos() > 0) cursor.mover(ARRIBA);
                }
                else if (teclaPresionada == ABAJO) {
                    if (cursor.getYPos() < 10) cursor.mover(ABAJO);
                }
                else if(key->code == sf::Keyboard::Key::A) { mov++; }
                else if(key->code == sf::Keyboard::Key::S) { mov--; }
            }
        }
    }
}

// ACTUALIZAR: Integración total del Manager y Personajes.
void Juego::actualizar() {
    if (!enMenu) {
        // Le pasamos las coordenadas del cursor al sistema de movimiento
        movimiento.calcularMovimiento(cursor.getXPos(), cursor.getYPos(), mov);
        // Prueba del algoritmo de Pathfinding de Mateo.:
        movimiento.buscarCamino(cursor.getXPos(), cursor.getYPos(), mov);
        // Lógica del manager que controla y cambia personajes (con SPACE)
        manager.moverpersonaje(pers[manager.getactual()]);
        manager.cambiarpersonaje(pers[manager.getactual()]);
    }
}

// RENDERIZAR: Dibujamos los 5 personajes del vector
void Juego::renderizar() {
    window.clear(sf::Color::Blue);

    if (enMenu) {
        menuPrincipal.draw(window);
    }
    else {
        tablero.render(window);

        // Renderizamos los 5 personajes del equipo tal como pedía el main viejo
        for(int v = 0; v < 5; v++) {
            manager.mostrarpersonaje(pers[v], window);
        }

        
        rendUi.renderCursor(cursor, window);
        rendUi.renderRangoMovimiento(movimiento.getValido(), window);
        drawMovRango(square, movimiento.getValido());

        // La posición en pixeles se calcula sola multiplicando por 64
    }

    window.display();
}

// FUNCIONES AUXILIARES
int Juego::cargarTexturasDeCeldas() {
    const char *nomArchivo[10] = {
        "Tiles/defaulttile.bmp",
        "Tiles/prado.bmp",
        "Tiles/bosque.bmp",
        "Tiles/montania.bmp",
        "Tiles/mar.bmp"
    };
    for(int i = 0; i < 5; i++) {
        if(!texCelda[i].loadFromFile(nomArchivo[i])) return -1;
    }
    return 0;
}

int Juego::cargarMapa(const char* nomArch) {
    const int tamFila = tablero.getMaxX();
    int i = 0;
    char tipoCelda;
    FILE *archMapa = fopen(nomArch, "rb");
    if(archMapa == nullptr) return -1;

    while(fread(&tipoCelda, 1, 1, archMapa) && (i < (tablero.getMaxX() * tablero.getMaxY()))) {
        switch(tipoCelda) {
            case '\n':
            case '\r':
                break;
            case '0': tablero.setCelda(new DefaultCelda(i % tamFila, i / tamFila, 255, texCelda[0])); i++; break;
            case 'P': tablero.setCelda(new CeldaTerrestre(i % tamFila, i / tamFila, 1, 1, texCelda[1])); i++; break;
            case 'B': tablero.setCelda(new CeldaTerrestre(i % tamFila, i / tamFila, 2, 2, texCelda[2])); i++; break;
            case 'M': tablero.setCelda(new CeldaTerrestre(i % tamFila, i / tamFila, 4, 3, texCelda[3])); i++; break;
            default: i++;
        }
    }
    fclose(archMapa);
    return 0;
}

void Juego::drawAt(sf::RectangleShape &sq, float ax, float ay) {
    sq.setPosition(sf::Vector2f(ax * 64, ay * 64));
    window.draw(sq);
}

void Juego::drawMovRango(sf::RectangleShape &sq, const bool *visitadas) {
    for(int iy = 0; iy < tablero.getMaxY(); iy++) {
        for(int ix = 0; ix < tablero.getMaxX(); ix++) {
            if(visitadas[ix + (iy * tablero.getMaxX())]) {
                drawAt(sq, ix, iy);
            }
        }
    }
}

void Juego::movRango(int ax, int ay, int amov, bool *visitadas) {
    if(!visitadas[ax + (ay * tablero.getMaxX())]) {
        visitadas[ax + (ay * tablero.getMaxX())] = true;
    }
    if(ay + 1 < tablero.getMaxY() && amov >= tablero.getCelda(ax, ay + 1)->getCostoMov())
        movRango(ax, ay + 1, amov - tablero.getCelda(ax, ay + 1)->getCostoMov(), visitadas);
    if(ax - 1 >= 0 && amov >= tablero.getCelda(ax - 1, ay)->getCostoMov())
        movRango(ax - 1 , ay, amov - tablero.getCelda(ax - 1 , ay)->getCostoMov(), visitadas);
    if(ay - 1 >= 0 && amov >= tablero.getCelda(ax, ay - 1)->getCostoMov())
        movRango(ax, ay - 1, amov - tablero.getCelda(ax, ay - 1)->getCostoMov(), visitadas);
    if(ax + 1 < tablero.getMaxX() && amov >= tablero.getCelda(ax + 1, ay)->getCostoMov())
        movRango(ax + 1, ay, amov - tablero.getCelda(ax + 1, ay)->getCostoMov(), visitadas);
}
