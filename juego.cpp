#include "juego.h"
#include "defaultcelda.h"
#include "celdaterrestre.h"
#include "proc_input.h"
#include "combate.h"
#include <cstdio>

// CONSTRUCTOR: Inicializa el Cursor y la Partida.
Juego::Juego() : window(sf::VideoMode({1024, 768}), "SFML 3"),
                 menuPrincipal(450, 250,
                                {"Jugar", "Opciones", "Salir"}
                              ),
                 enMenu(true),
                 cursor(0, 0),
                 partida(0, 0),
                 mov(3),
                 texturas("archivos.txt"),
                 tablero(64, 15, 10),
                 rendUi(&tablero),
                 movimiento(3, 3, &tablero, pers)
{
    window.setFramerateLimit(60);

    Estado = CURSOR_LIBRE;
    personajeSeleccionado = nullptr;
    teclaPresionada = 0;
    cargarMapa("nivel1.txt");

    agregarPersonaje(TIPO_PERSONAJE::JUGADOR, 1, 1);
    agregarPersonaje(TIPO_PERSONAJE::JUGADOR, 2, 1);
    agregarPersonaje(TIPO_PERSONAJE::JUGADOR, 3, 1);
    agregarPersonaje(TIPO_PERSONAJE::JUGADOR, 4, 1);
    agregarPersonaje(TIPO_PERSONAJE::JUGADOR, 5, 1);

    movimiento.setEnemigos(pers);

    for(unsigned int i = 0; i < pers.size(); i++)
      pers[i].setSprite(*texturas.getPersonaje(i % 4));

    Estado = CURSOR_LIBRE;

    personajeSeleccionado = nullptr;
}

void Juego::ejecutar()
{
    while (window.isOpen())
    {
        procesarEventos();
        actualizar();
        renderizar();
    }
}

// EVENTOS: Movemos el cursor con el ENUM de constantes.h que hizo lucas.
void Juego::procesarEventos()
{
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
            else
            {
                // Control del movimiento usando la clase Cursor de lucas.
                if ( Estado == PERSONAJE_SELECCIONADO)
                {
                    if(teclaPresionada == ENTER)
                    {
                        movimiento.setDestino(cursor.getXPos(), cursor.getYPos());
                        if (!movimiento.Alcanzable(cursor.getXPos(), cursor.getYPos()) ||
                            managerpersonaje::comprobarLugarTablero(cursor.getXPos(), cursor.getYPos(), pers) != -1)
                        {
                            Estado = CURSOR_LIBRE;
                            teclaPresionada = NULO;
                            personajeSeleccionado = nullptr;
                            return;
                        }
                        else
                        {
                            movimiento.buscarCamino(personajeSeleccionado->getPosx(), personajeSeleccionado->getPosy(), mov);
                            manager.resetCaminoIndice();
                            Estado = ANIMACION_BLOQUEANTE;
                            //  manager.mostrarpersonaje(*personajeSeleccionado, window);
                            //moverPersonajeSeleccionado();
                        }
                    }
                }
                if (Estado == CURSOR_LIBRE && teclaPresionada == ENTER)
                {
                    personaje* P = GetPersonajeSeleccionado();
                    if (P != nullptr && !P->getYaActuo())
                    {
                        personajeSeleccionado = P;
                        Estado = MENU_INGAME; // Cambiamos al nuevo estado
                        teclaPresionada = NULO;

                        // Si había un menú viejo dando vueltas, lo borramos
                        if (menuAccion != nullptr) delete menuAccion;

                        // Creamos el menú pasándole las coordenadas del personaje en píxeles (+64 a la derecha)
                        menuAccion = new Menu(P->getPosxPxl() + 64, P->getPosyPxl(), {"Mover", "Atacar", "Esperar", "Cancelar"});
                    }
                }
                // Si se selecciona un personaje, el estado pasa a PersonajeSeleccionado.
            }
            if(Estado == CURSOR_LIBRE || Estado == PERSONAJE_SELECCIONADO)
            {
                if(teclaPresionada == ARRIBA)
                {
                    if(cursor.getYPos() > 0)
                        cursor.mover(ARRIBA);
                }
                else if (teclaPresionada == ABAJO)
                {
                    if(cursor.getYPos() < tablero.getMaxY() - 1)
                        cursor.mover(ABAJO);
                }
                else if(teclaPresionada == IZQUIERDA)
                {
                    if(cursor.getXPos() > 0)
                        cursor.mover(IZQUIERDA);
                }
                else if(teclaPresionada == DERECHA)
                {
                    if(cursor.getXPos() < tablero.getMaxX() - 1)
                        cursor.mover(DERECHA);
                }
            }
            else if(Estado == PREPARAR_ATAQUE)
            {
                // Las flechas cambian hacia dónde mira el personaje para elegir el objetivo
                manager.cambiardireccion(pers, teclaPresionada);

                // Si se presiona ENTER (o SPACE) confirmamos el ataque
                if(teclaPresionada == ENTER)
                {
                //aca asigna los lugares para la animacion de golpe
                    animacion.asignaranimacion(pers,ataque.getimpactos(),ataque.getdaniosimpactos(),ataque.getcantidadimpactos());
                    Estado=ANIMACION_DAÑO;
                    cont=0;
                    // Aca podria ir el codigo para restar vida....
                    //
                    for(int i = 0; i < ataque.getcantidadimpactos(); i++)
                    {
                       Combate combate(&tablero, personajeSeleccionado, &pers[ataque.getimpactos()[i]]);
                       combate.pelea();
                       cout << "Atacante: " << personajeSeleccionado->getHp() << "/" << personajeSeleccionado->getMaxHp() << endl;
                       cout << "Defendiente: " << pers[ataque.getimpactos()[i]].getHp() << "/" << pers[ataque.getimpactos()[i]].getMaxHp() << endl << endl;
                    }
                    

                    
                    // El personaje atacó, su turno termina.
                    personajeSeleccionado->setYaActuo(true);
                    // Estado = CURSOR_LIBRE; <----ahora pasa a un estado distinto
                    personajeSeleccionado = nullptr;
                }
                // Si se presiona RETROCESO o F, cancelamos y volvemos al mapa
                else if ((teclaPresionada == RETROCESO || teclaPresionada == F))
                {
                    // Validacion
                    if (personajeSeleccionado != nullptr)
                    {
                        personajeSeleccionado->setYaActuo(true);
                    }
                    // No gastamos el turno y volvemos al estado CURSOR_LIBRE.
                    Estado = CURSOR_LIBRE;
                    personajeSeleccionado = nullptr;
                }
            }
            if (Estado == MENU_INGAME && menuAccion != nullptr)
            {
                if (teclaPresionada == ARRIBA) menuAccion->moveUp();
                else if (teclaPresionada == ABAJO) menuAccion->moveDown();
                else if (teclaPresionada == ENTER)
                {
                    int opcion = menuAccion->getPressedItem();

                    if (opcion == 0) // Mover
                    {
                        Estado = PERSONAJE_SELECCIONADO;
                        movimiento.calcularMovimiento(personajeSeleccionado->getPosx(), personajeSeleccionado->getPosy(), mov);
                    }
                    else if (opcion == 1) // Atacar
                    {
                        Estado = PREPARAR_ATAQUE;
                    }
                    else if (opcion == 2) // Esperar
                    {
                        personajeSeleccionado->setYaActuo(true);
                        Estado = CURSOR_LIBRE;
                        personajeSeleccionado = nullptr;
                    }
                    else if (opcion == 3) // Cancelar
                    {
                        Estado = CURSOR_LIBRE;
                        personajeSeleccionado = nullptr;
                    }

                    // Borramos el menú porque ya se eligió una opción
                    delete menuAccion;
                    menuAccion = nullptr;
                }
            }
            teclaPresionada = NULO;
        }
    }
}

// ACTUALIZAR: Integracion total del Manager y Personajes.
void Juego::actualizar()
{
    if (enMenu)
        return;
    if(Estado == CURSOR_LIBRE)
    {
        /// Desactivo el sistema VIEJO.
        //manager.moverpersonaje(pers[manager.getactual()]);
        //manager.cambiarpersonaje(pers[manager.getactual()]);
    }
    if (Estado == PREPARAR_ATAQUE)
    {
    }

    manager.actualizarpersonaje(pers);
    if(Estado == ANIMACION_BLOQUEANTE)
    {
        if (!manager.moverpersonaje(*personajeSeleccionado, movimiento.getCamino()))
        {
            Estado = CURSOR_LIBRE;
            personajeSeleccionado->setYaActuo(true);
        }
    }
    if(todasLasUnidadesActuaron())
    {
        partida.pasarTurno();
        resetearAccionesJugador();
    }
}
        // FUNCIONES AUXILIARES

int Juego::cargarMapa(const char *nomArch)
{
    const int tamFila = tablero.getMaxX();
    int i = 0;
    char tipoCelda;
    FILE *archMapa = fopen(nomArch, "rb");
    if (archMapa == nullptr)
        return -1;

    while (fread(&tipoCelda, 1, 1, archMapa) && (i < (tablero.getMaxX() * tablero.getMaxY())))
    {
        switch (tipoCelda)
        {
        case '\n':
        case '\r':
            break;
        case '0':
            tablero.setCelda(new DefaultCelda(i % tamFila, i / tamFila, 255, *texturas.getCelda(DEFAULT)));
            i++;
            break;
        case 'P':
            tablero.setCelda(new CeldaTerrestre(i % tamFila, i / tamFila, 1, 1, *texturas.getCelda(PRADO)));
            i++;
            break;
        case 'B':
            tablero.setCelda(new CeldaTerrestre(i % tamFila, i / tamFila, 2, 2, *texturas.getCelda(BOSQUE)));
            i++;
            break;
        case 'M':
            tablero.setCelda(new CeldaTerrestre(i % tamFila, i / tamFila, 4, 3, *texturas.getCelda(MONTANIA)));
            i++;
            break;
        default:
            i++;
        }
    }
    fclose(archMapa);
    return 0;
}

void Juego::moverPersonajeSeleccionado()
{
    if (personajeSeleccionado == nullptr)
        return;
    const int *camino = movimiento.getCamino();
    int x = personajeSeleccionado->getPosx();
    int y = personajeSeleccionado->getPosy();
    for (int i = 0; i < profundidadMax && camino[i] != -1; i++)
    {
        switch (camino[i])
        {
        case ARRIBA:
            y -= 1;
            break;
        case ABAJO:
            y += 1;
            break;
        case IZQUIERDA:
            x -= 1;
            break;
        case DERECHA:
            x += 1;
            break;
        }
    }
    personajeSeleccionado->setposx(x * 64);
    personajeSeleccionado->setposy(y * 64);
    personajeSeleccionado->setsprite(*texturas.getPersonaje(0));
    personajeSeleccionado->setYaActuo(true);
    Estado = CURSOR_LIBRE;
    personajeSeleccionado = nullptr;
}

// RENDERIZAR: Dibujamos los 5 personajes del vector
void Juego::renderizar()
{
    window.clear(sf::Color::Blue);

    if (enMenu)
    {
        menuPrincipal.draw(window);
    }
    else
    {
        tablero.render(window);

        // Renderizamos los 5 personajes del equipo tal como pedIa el main viejo
        manager.actualizarpersonaje(pers);
        manager.mostrarpersonaje(pers, window);
        if (Estado == PREPARAR_ATAQUE)
        {
            ataque.prepararataque(pers[manager.getactual()].getdireccion(), window, pers, manager);
          }

        if (Estado == CURSOR_LIBRE || Estado == PERSONAJE_SELECCIONADO)
            rendUi.renderCursor(cursor, window);
        if (Estado == PERSONAJE_SELECCIONADO)
        {
            rendUi.renderRangoMovimiento(movimiento.getValido(), window);
        }
        if (Estado == MENU_INGAME && menuAccion != nullptr)
        {
            menuAccion->draw(window);
        }
    }
    if(Estado==ANIMACION_DAÑO)
    {
      animacion.mostraranimacion(window);
      cont++;
      if(cont>80){Estado=CURSOR_LIBRE;cont=0;}
    }
    window.display();
}


personaje *Juego::GetPersonajeSeleccionado()
{
    for (unsigned int i = 0; i < pers.size(); i++)
    {
        if (pers[i].getPosx() == cursor.getXPos() && pers[i].getPosy() == cursor.getYPos())
        {
            manager.setactual(i);
            return &pers[i];
        }
    }
    return nullptr;
}
bool Juego::todasLasUnidadesActuaron()
{
    for (unsigned int i = 0; i < pers.size(); i++)
    {
        if (!pers[i].getYaActuo())
        {
            return false;
        }
    }
    return true;
}

void Juego::resetearAccionesJugador()
{
    for (unsigned int i = 0; i < pers.size(); i++)
    {
        pers[i].setYaActuo(false);
    }
}

void Juego::agregarPersonaje(TIPO_PERSONAJE tipoPJ, int x, int y)
{
    personaje nuevo(&tablero, pers.size(), tipoPJ);

    manager.Asignarpersonajes(nuevo, tipoPJ, x, y);

    pers.push_back(nuevo);

    manager.setcantidad(pers.size());
}
