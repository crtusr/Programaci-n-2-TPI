#include "juego.h"
#include "defaultcelda.h"
#include "celdaterrestre.h"
#include "proc_input.h"
#include "utilidades.h"
#include "combate.h"
#include "adminarchivo.h"
#include <cstdio>

// CONSTRUCTOR: Inicializa el Cursor y la Partida.
Juego::Juego() : window(sf::VideoMode({1024, 768}), "SFML 3"),
                 menuPrincipal(450, 250,
                               {"Jugar", "Opciones", "Salir"}),
                 enMenu(true),
                 cursor(0, 0),
                 partida(0, 0),
                 mov(3),
                 texturas("archivos.txt"),
                 tablero(64, 17, 12),
                 rendUi(&tablero),
                 movimiento(3, 3, &tablero, persNJ)
{

    window.setFramerateLimit(60);
    Estado = CURSOR_LIBRE;
    personajeSeleccionado = nullptr;
    teclaPresionada = 0;
    cargarMapa("nivel1.txt");

    SpawnPersonaje();


    movimiento.setEnemigos(persNJ);


    Estado = CURSOR_LIBRE;

    personajeSeleccionado = nullptr;
    sf::FloatRect newSize(sf::Vector2f(0, 0), 
                          sf::Vector2f(tablero.getMaxX() * tablero.getTamCeldaPixeles(),
                                       tablero.getMaxY() * tablero.getTamCeldaPixeles()));
    window.setView(sf::View(newSize));
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
        else if (const auto *resized = event->getIf<sf::Event::Resized>())
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
                if (teclaPresionada == ARRIBA)
                    menuPrincipal.moveUp();
                else if (teclaPresionada == ABAJO)
                    menuPrincipal.moveDown();
                else if (teclaPresionada == ENTER)
                {
                    int opcion = menuPrincipal.getPressedItem();
                    if (opcion == 0)
                        enMenu = false;
                    else if (opcion == 2)
                        window.close();
                }
            }
            else
            {
                // Control del movimiento usando la clase Cursor de lucas.
                if (Estado == PERSONAJE_SELECCIONADO)
                {
                    if (teclaPresionada == ENTER)
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
                            // moverPersonajeSeleccionado();
                        }
                    }
                }
                if (Estado == CURSOR_LIBRE && teclaPresionada == ENTER)
                {
                    personaje *P = GetPersonajeSeleccionado();
                    if (P != nullptr && !P->getYaActuo())
                    {
                        personajeSeleccionado = P;
                        /***********************ES UN MENSAJE POR CONSOLA QUE ME DICE LA INFORMACION DEL PERSONAJE SELECCIONADO(agregen mas informacion si la necesitan)*************************/
                        std::cout << "Seleccionaste personaje ID = " << P->getId()
                                  << " | Tipo = " << tipoToString(P->getTipo())
                                  << " | Pos(" << P->getPosx() << ", " << P->getPosy() << ")"
                                  << " |TURNO(" << partida.getTurno() << "," << partida.getRonda() << ")"
                                  << " |Hp = " << P->getMaxHpReal() << "/" << P ->getHpReal()
                                  << " |Fr = " << P->getFuerzaReal()
                                  << " |Def = " << P->getDefensaReal() << "."
                                  << std::endl;
                        /*************************************************************************************************************************************************************************/
                        /*for(int i = 0; i <pers.size(); i++){
                                if(&pers[i] == P){
                                    manager.setActual(i);   // ← ACÁ SE SETEA EL ACTUAL
                                    break;
                                }
                        }*/
                        Estado = PERSONAJE_SELECCIONADO;
                        Estado = MENU_INGAME; // Cambiamos al nuevo estado
                        teclaPresionada = NULO;

                        // Si había un menú viejo dando vueltas, lo borramos
                        if (menuAccion != nullptr)
                            delete menuAccion;

                        // Creamos el menú pasándole las coordenadas del personaje en píxeles (+64 a la derecha)
                        menuAccion = new Menu(P->getPosxPxl() + 64, P->getPosyPxl(), {"Mover", "Atacar", "Esperar", "Cancelar"});
                    }
                }
                // Si se selecciona un personaje, el estado pasa a PersonajeSeleccionado.
            }
            if (Estado == CURSOR_LIBRE || Estado == PERSONAJE_SELECCIONADO)
            {
                if (teclaPresionada == ARRIBA)
                {
                    if (cursor.getYPos() > 0)
                        cursor.mover(ARRIBA);
                }
                else if (teclaPresionada == ABAJO)
                {
                    if (cursor.getYPos() < tablero.getMaxY() - 1)
                        cursor.mover(ABAJO);
                }
                else if (teclaPresionada == IZQUIERDA)
                {
                    if (cursor.getXPos() > 0)
                        cursor.mover(IZQUIERDA);
                }
                else if (teclaPresionada == DERECHA)
                {
                    if (cursor.getXPos() < tablero.getMaxX() - 1)
                        cursor.mover(DERECHA);
                }
            }
            else if (Estado == PREPARAR_ATAQUE)
            {
                // Las flechas cambian hacia dónde mira el personaje para elegir el objetivo
                manager.cambiardireccion(pers, teclaPresionada);

                // Si se presiona ENTER (o SPACE) confirmamos el ataque
                if (teclaPresionada == ENTER)
                {
                //aca asigna los lugares para la animacion de golpe
                    animacion.asignaranimacion(persNJ,ataque); //<--esta funcion tiene que ajustarse dependiendo quien recive el golpe
                    Estado=ANIMACION_DAÑO;
                    cont=0;
                    // Aca podria ir el codigo para restar vida....
                    //
                    for(int i = 0; i < ataque.getcantidadimpactos(); i++)
                    {
                       Combate combate(&tablero, personajeSeleccionado, &persNJ[ataque.getimpactos()[i]]);
                       combate.pelea();
                       cout << "Atacante: " << personajeSeleccionado->getHpReal() << "/" << personajeSeleccionado->getMaxHpReal() << endl;
                       cout << "Defendiente: " << persNJ[ataque.getimpactos()[i]].getHpReal() << "/" << persNJ[ataque.getimpactos()[i]].getMaxHpReal() << endl << endl;
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
                if (teclaPresionada == ARRIBA)
                    menuAccion->moveUp();
                else if (teclaPresionada == ABAJO)
                    menuAccion->moveDown();
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

    //  manager.actualizarpersonaje(pers);
  //  manager.actualizarpersonaje(persNJ);
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
        case '1':
            tablero.setCelda(new DefaultCelda(i % tamFila, i / tamFila, 255, *texturas.getCelda(BOSQUE_ESPESO)));
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

        // Renderizamos los 5 personajes del equipo tal como ped�a el main viejo
        manager.actualizarpersonaje(pers);
        manager.actualizarpersonaje(persNJ);
        manager.mostrarpersonaje(pers, window);
        animacion.mostrarvida(window,pers);
        animacion.mostrarvida(window,persNJ);

        for (personaje &nose : persNJ)
            window.draw(nose.getsprite());

        if (Estado == PREPARAR_ATAQUE)
        {
			     //getopciondeataque es temporal se va a reemplazar por el ataque que seleccione el menu de ataques
            ataque.prepararataque(pers[manager.getactual()].getdireccion(), window, pers, persNJ, manager,ataque.getopciondeataque());
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
            manager.setActual(i);
            return &pers[i];
        }
    }
    return nullptr;
}
bool Juego::todasLasUnidadesActuaron()
{
    for (int i = 0; i < pers.size(); i++)
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
    for (int i = 0; i < pers.size(); i++)
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

void Juego::agregarPersonajeNJ(TIPO_PERSONAJE tipoPJ, int x, int y)
{
    personaje nuevo(&tablero, persNJ.size(), tipoPJ);

    ia.registrarPNJ(nuevo, tipoPJ, x, y);

    persNJ.push_back(nuevo);
};

void Juego::SpawnPersonaje(){
    AdminArchivo personajes("personajes1.txt");
    int x, y, trabajo, maxHp, fuerza, defensa;
    const char separador = ';';
    personajes.abrir();
    int cantPJ = personajes.leerNumero();
    for(int i = 0; i < cantPJ; i++)
    {
      personajes.avanzarHastaChar(separador);
      x = personajes.leerNumero();

      personajes.avanzarHastaChar(separador);
      y = personajes.leerNumero();

      personajes.avanzarHastaChar(separador);
			trabajo = personajes.leerNumero();

      personajes.avanzarHastaChar(separador);
			maxHp = personajes.leerNumero();

      personajes.avanzarHastaChar(separador);
			fuerza = personajes.leerNumero();

      personajes.avanzarHastaChar(separador);
			defensa = personajes.leerNumero();

      agregarPersonaje(TIPO_PERSONAJE::JUGADOR, x, y);
      pers[i].setTrabajo(trabajos.getClase(trabajo));
      pers[i].setSprite(*texturas.getPersonaje(trabajo));
      pers[i].setMaxHp(maxHp);
      pers[i].setHp(maxHp);
      pers[i].setFuerza(fuerza);
      pers[i].setDef(defensa);
    }

    int cantPNJ = personajes.leerNumero();

    for(int i = 0; i < cantPNJ; i++)
    {
      personajes.avanzarHastaChar(separador);
      x = personajes.leerNumero();

      personajes.avanzarHastaChar(separador);
      y = personajes.leerNumero();

      personajes.avanzarHastaChar(separador);
			trabajo = personajes.leerNumero();

      personajes.avanzarHastaChar(separador);
			maxHp = personajes.leerNumero();

      personajes.avanzarHastaChar(separador);
			fuerza = personajes.leerNumero();

      personajes.avanzarHastaChar(separador);
			defensa = personajes.leerNumero();

      agregarPersonajeNJ(TIPO_PERSONAJE::NO_JUGADOR, x, y);
      persNJ[i].setTrabajo(trabajos.getClase(trabajo));
      persNJ[i].setSprite(*texturas.getPersonaje(trabajo));
      persNJ[i].setMaxHp(maxHp);
      persNJ[i].setHp(maxHp);
      persNJ[i].setFuerza(fuerza);
      persNJ[i].setDef(defensa);
    }
    /*
    agregarPersonaje(TIPO_PERSONAJE::JUGADOR, 1, 1, CLASE_GUERRERO);
    agregarPersonaje(TIPO_PERSONAJE::JUGADOR, 2, 1, CLASE_ARQUERO);
    agregarPersonaje(TIPO_PERSONAJE::JUGADOR, 3, 1, CLASE_MEDICO);
    agregarPersonaje(TIPO_PERSONAJE::JUGADOR, 4, 1, CLASE_GUERRERO);
    agregarPersonaje(TIPO_PERSONAJE::JUGADOR, 5, 1,CLASE_ARQUERO);
    agregarPersonajeNJ(TIPO_PERSONAJE::NO_JUGADOR, 1, 3);
    agregarPersonajeNJ(TIPO_PERSONAJE::NO_JUGADOR, 2, 3);
    agregarPersonajeNJ(TIPO_PERSONAJE::NO_JUGADOR, 3, 3);
    agregarPersonajeNJ(TIPO_PERSONAJE::NO_JUGADOR, 4, 3);
    agregarPersonajeNJ(TIPO_PERSONAJE::NO_JUGADOR, 5, 3);
    */
    personajes.cerrar();
}
