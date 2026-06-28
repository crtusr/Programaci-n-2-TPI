#include "juego.h"
#include "defaultcelda.h"
#include "celdaterrestre.h"
#include "proc_input.h"
#include "utilidades.h"
#include "combate.h"
#include "adminarchivo.h"
#include <cstdio>
#include <iostream>

using namespace std;
// para un pull
// CONSTRUCTOR: Inicializa el Cursor, la Partida y carga los archivos dinámicos.
Juego::Juego(const char *archivoMapa, const char *archivoPersonajes) :

    cursor(0, 0),
    partida(0, 0),
    texturas("archivos.txt"),
    tablero(64, 0, 0),
    rendUi(&tablero),
    movimiento(3, 3, &tablero, &persNJ),
    ia(&tablero, &manager)
{
    nivelSuperado = false;
    jugadorQuiereSalir = false;

    Estado = CURSOR_LIBRE;
    personajeSeleccionado = nullptr;
    teclaPresionada = 0;
    menuSubOpciones = nullptr;
    menuAccion = nullptr;
    menuPausa = nullptr;

    // Cargamos los archivos que nos pasó el Manager
    tablero.resize(archivoMapa);
    movimiento.resizeGrid(&tablero);
    cargarMapa(archivoMapa);
    SpawnPersonaje(archivoPersonajes);

    movimiento.setEnemigos(&persNJ);

    Estado = CURSOR_LIBRE;
    personajeSeleccionado = nullptr;
}

bool Juego::ejecutar(sf::RenderWindow &window)
{
    // Ajustamos la cámara al tamaño del tablero justo antes de empezar a jugar
    sf::FloatRect newSize(sf::Vector2f(0, 0),
                          sf::Vector2f(tablero.getMaxX() * tablero.getTamCeldaPixeles(),
                                       tablero.getMaxY() * tablero.getTamCeldaPixeles()));
    window.setView(sf::View(newSize));
    pers[0].restarHp(30); // BORRAR ANTES DE ENTREGAR
    pers[1].restarHp(30);
    // El bucle ahora depende de la ventana prestada y de nuestras banderas
    while (window.isOpen() && !nivelSuperado && !jugadorQuiereSalir)
    {
        procesarEventos(window);
        if(Estado != ANIMACION_BLOQUEANTE && Estado != ANIMACION_DAÑO && partida.getTurno() == 1)
            procesarIA(window);
        actualizar();
        renderizar(window);
    }

    // Si salió del bucle porque ganó, devuelve true. Si salió por la 'X' o retroceso, false.
    return nivelSuperado;
}

void Juego::procesarEventos(sf::RenderWindow &window)
{
    while (const std::optional<sf::Event> event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            // La 'X' de la ventana ahora cierra todo el juego directamente
            window.close();
        }
        else if (const auto *resized = event->getIf<sf::Event::Resized>())
        {
            sf::FloatRect newSize(sf::Vector2f(0, 0), sf::Vector2f(resized->size.x, resized->size.y));
            window.setView(sf::View(newSize));
        }
        else if (partida.getTurno() == 1)
        {
            return;
        }
        else if (const auto *key = event->getIf<sf::Event::KeyPressed>())
        {
            if (key->code == sf::Keyboard::Key::Escape)
            {
                if (Estado != PAUSA)
                {
                    Estado = PAUSA;
                    std::vector<std::string> opcionesPausa = {"Continuar", "Volver al Menu Principal"};
                    menuPausa = new Menu(400, 300, opcionesPausa);
                }
                else
                {
                    Estado = CURSOR_LIBRE;
                    if (menuPausa != nullptr)
                    {
                        delete menuPausa;
                menuPausa = nullptr;
                    }
                }
                return;
            }
            // 2. SEGUNDO: Si no apretó ESC, procesamos el movimiento y las demás teclas
            teclaPresionada = procesar.tecla(key->code);

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
                        movimiento.buscarCamino(personajeSeleccionado->getPosx(), personajeSeleccionado->getPosy(), personajeSeleccionado->getMovReal());
                        manager.resetCaminoIndice();
                        Estado = ANIMACION_BLOQUEANTE;
                    }
                }
                // --- NUEVO: BOTÓN CANCELAR MOVIMIENTO ---
                else if (teclaPresionada == RETROCESO || teclaPresionada == F)
                {
                    Estado = MENU_INGAME;
                    teclaPresionada = NULO;
                }
                // Aca tambien va la logica del menu dinamico.
                menuAccion = new Menu(personajeSeleccionado->getPosxPxl() + 64, personajeSeleccionado->getPosyPxl(), {"Mover", "Atacar", "Esperar", "Cancelar"});
            }
        }
        if (Estado == CURSOR_LIBRE && teclaPresionada == ENTER)
        {
            personaje *P = GetPersonajeSeleccionado();
            if (P != nullptr && !P->getYaActuo())
            {
                personajeSeleccionado = P;
                Estado = MENU_INGAME;
                teclaPresionada = NULO;

                if (menuAccion != nullptr)
                    delete menuAccion;

                // 1. Obtenemos el trabajo del personaje seleccionado
                claseTrabajo* trabajoActual = P->getTrabajo();

                // 2. Extraemos su ID.
                int idClase = (trabajoActual != nullptr) ? trabajoActual->getIdTrabajo() : 0;

                // 3. El Switch Dinámico de Menús
                switch (idClase)
                {
                case 1: // Arquero / Tirador
                    menuAccion = new Menu(P->getPosxPxl() + 64, P->getPosyPxl(), {"Mover", "Disparar", "Esperar", "Cancelar"});
                    break;

                case 2: // Médico
                    menuAccion = new Menu(P->getPosxPxl() + 64, P->getPosyPxl(), {"Mover", "Curar", "Esperar", "Cancelar"});
                    break;

                default: // Guerrero (0) o cualquier otra clase no definida
                    menuAccion = new Menu(P->getPosxPxl() + 64, P->getPosyPxl(), {"Mover", "Atacar", "Esperar", "Cancelar"});
                    break;
                }
            }
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
            manager.cambiardireccion(pers, teclaPresionada);

            if (teclaPresionada == ENTER)
            {
                // ACTUALIZADO: Nueva lógica de animación de lucas.
                if(ataque.getopciondeataque() == CURA || ataque.getopciondeataque() == CURA_GRANDE)
                {
                    declararCuracion(pers, personajeSeleccionado);
                }
                else
                {
                    declararAtaque(pers, persNJ, personajeSeleccionado);
                }

                personajeSeleccionado->setYaActuo(true);
                personajeSeleccionado = nullptr;
            }
            else if ((teclaPresionada == RETROCESO || teclaPresionada == F))
            {
                Estado = MENU_INGAME;
                teclaPresionada = NULO;
                menuAccion = new Menu(personajeSeleccionado->getPosxPxl() + 64, personajeSeleccionado->getPosyPxl(), {"Mover", "Atacar", "Esperar", "Cancelar"});
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
                // AQUÍ declaramos la variable opcion
                int opcion = menuAccion->getPressedItem();

                if (opcion == 0 && personajeSeleccionado->getYaMovio() == false) // Mover
                {
                    Estado = PERSONAJE_SELECCIONADO;
                    movimiento.calcularMovimiento(personajeSeleccionado->getPosx(), personajeSeleccionado->getPosy(), personajeSeleccionado->getMovReal());
                }
                else if (opcion == 1) // Habilidades / Ataques
                {
                    Estado = SUBMENU_ATAQUES;
                    claseTrabajo* trabajoAct = personajeSeleccionado->getTrabajo();
                    int idC = (trabajoAct != nullptr) ? trabajoAct->getIdTrabajo() : 0;
                    int subX = personajeSeleccionado->getPosxPxl() + 192;
                    int subY = personajeSeleccionado->getPosyPxl();

                    if (menuSubOpciones != nullptr) delete menuSubOpciones;

                    switch (idC)
                    {
                        case 1:
                            menuSubOpciones = new Menu(subX, subY, {"Flecha Comun", "Granada", "Volver"});
                            break;
                        case 2:
                            menuSubOpciones = new Menu(subX, subY, {"Curacion", "Curar Area", "Volver"});
                            break;
                        default:
                            menuSubOpciones = new Menu(subX, subY, {"Golpe Espada", "Corte Fuerte", "Volver"});
                            break;
                    }
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

                // Borramos solo si no estamos en submenú
                if (Estado != MENU_INGAME && Estado != SUBMENU_ATAQUES)
                {
                    delete menuAccion;
                    menuAccion = nullptr;
                }
            }
        }
        // --- AGREGA ESTO AQUÍ: Control del Submenú ---
        else if (Estado == SUBMENU_ATAQUES && menuSubOpciones != nullptr)
        {
            if (teclaPresionada == ARRIBA)
                menuSubOpciones->moveUp();
            else if (teclaPresionada == ABAJO)
                menuSubOpciones->moveDown();
            else if (teclaPresionada == ENTER)
            {
                int subOpcion = menuSubOpciones->getPressedItem();

                if (subOpcion == 2) // Opción "Volver"
                {
                    Estado = MENU_INGAME; // Volvemos al principal
                    delete menuSubOpciones;
                    menuSubOpciones = nullptr;
                }
                else
                {
                    ataque.setOpcionDeAtaque(personajeSeleccionado->getTrabajo()->getOptAtk(subOpcion));
                    // Aca hay que definir que qué hace cada ataque
                    std::cout << "Ataque seleccionado: " << subOpcion << std::endl;
                    // Por ahora, para probar que funciona:
                    Estado = PREPARAR_ATAQUE; // Saltamos a la selección de objetivo.
                }
            }
        }
                // --- NUEVO: Control del Menú de Pausa ---
        else if (Estado == PAUSA && menuPausa != nullptr)
        {
            if (teclaPresionada == ARRIBA)
                menuPausa->moveUp();
            else if (teclaPresionada == ABAJO)
                menuPausa->moveDown();
            else if (teclaPresionada == ENTER)
            {
                int seleccion = menuPausa->getPressedItem();

                if (seleccion == 0) // Opción "Continuar"
                {
                    Estado = CURSOR_LIBRE;
                    delete menuPausa;
                    menuPausa = nullptr;
                }
                else if (seleccion == 1) // Opción "Volver al Menú Principal"
                {
                    jugadorQuiereSalir = true; // Esto le avisa al juego que debe salir

                    delete menuPausa;
                    menuPausa = nullptr;
                }
            }
        }
        teclaPresionada = NULO;
    }
}
void Juego::procesarIA(sf::RenderWindow &window)
{
    EstadoIA = DECIDIENDO;
    std::pair<int, int> persMasCercano;

    int idMasCercano;
    int cantPasos;

    std::pair<int, int> coordenadas;
    int coordenadaX;
    int coordenadaY;

    while(ia.getContIA() < persNJ.size() && (persNJ[ia.getContIA()].getYaActuo() || persNJ[ia.getContIA()].getHpReal() == 0))
    {
        if(persNJ[ia.getContIA()].getHpReal() == 0)
          persNJ[ia.getContIA()].setYaActuo(true);
        ia.inContIA();
    }

    if (ia.getContIA()>=persNJ.size())
        return;



    if (EstadoIA == DECIDIENDO)
    {
        manager.setActual(ia.getContIA());
        persMasCercano = ia.detectarEnemigoCercano(pers, persNJ);
        idMasCercano = persMasCercano.first;
        cantPasos = persMasCercano.second;

        movimiento.calcularMovimiento(persNJ[ia.getContIA()].getPosx(), persNJ[ia.getContIA()].getPosy(), persNJ[ia.getContIA()].getMovReal());

        std::pair<int, int> coordenadasA = ia.casillaValida(idMasCercano, pers, persNJ, movimiento);
        int coordenadaAX = coordenadasA.first;
        int coordenadaAY = coordenadasA.second;


        if(cantPasos == 1)
        {
            EstadoIA = DALE_MATRACA;
        }
        else if(movimiento.Alcanzable(coordenadaAX, coordenadaAY) && !persNJ[ia.getContIA()].getYaMovio())
        {
            EstadoIA = ENEMIGO_EN_RANGO;
        }
        else if(cantPasos <= persNJ[ia.getContIA()].getMovReal() * 2 && !persNJ[ia.getContIA()].getYaMovio())
        {
            EstadoIA = ENEMIGO_CERCA;
        }
        /*else 
        {
            EstadoIA = ENEMIGO_LEJOS;
        }*/
    }
    
    if(EstadoIA == DALE_MATRACA)
    {
        manager.setActual(ia.getContIA());
          int direccion = -1;
          if(persNJ[ia.getContIA()].getPosx() - pers[idMasCercano].getPosx() == 1)
            direccion = IZQUIERDA;
          else if(persNJ[ia.getContIA()].getPosx() - pers[idMasCercano].getPosx() == -1)
            direccion = DERECHA;
          else if(persNJ[ia.getContIA()].getPosy() - pers[idMasCercano].getPosy() == 1)
            direccion = ARRIBA;
          else if(persNJ[ia.getContIA()].getPosy() - pers[idMasCercano].getPosy() == -1)
            direccion = ABAJO;
          if(direccion == -1)
            cout << "no funciono" << endl;
          persNJ[ia.getContIA()].setdireccion(direccion);
          ataque.setOpcionDeAtaque(SIMPLE);
          ataque.prepararataque(direccion, window, persNJ, pers, manager, SIMPLE);
          declararAtaque(persNJ, pers, &pers[ia.getContIA()]);
          persNJ[ia.getContIA()].setYaActuo(true);
          return;
    }
    else if(persNJ[ia.getContIA()].getYaMovio())
      persNJ[ia.getContIA()].setYaActuo(true);
    if(EstadoIA == ENEMIGO_EN_RANGO)
    {   
        manager.setActual(ia.getContIA());
        coordenadas = ia.casillaValida(idMasCercano, pers, persNJ, movimiento);
        coordenadaX = coordenadas.first;
        coordenadaY = coordenadas.second;
    }

    if (EstadoIA == ENEMIGO_CERCA)
    {
        manager.setActual(ia.getContIA());
        coordenadas = ia.acercarceAlEnemigo(idMasCercano, pers, persNJ, movimiento);
        coordenadaX = coordenadas.first;
        coordenadaY = coordenadas.second;
        persNJ[ia.getContIA()].setYaMovio(true);
    }

    movimiento.setDestino(coordenadaX, coordenadaY);

    movimiento.buscarCamino(persNJ[ia.getContIA()].getPosx(), persNJ[ia.getContIA()].getPosy(), persNJ[ia.getContIA()].getMovReal());
    manager.resetCaminoIndice();

    Estado = ANIMACION_BLOQUEANTE;
}
// ACTUALIZAR: Integracion total del Manager y Personajes.
void Juego::actualizar()
{
    if (Estado == ANIMACION_BLOQUEANTE)
    {
        if(partida.getTurno() == 0)
        {
            if (!manager.moverpersonaje(*personajeSeleccionado, movimiento.getCamino()))
            {
                Estado = MENU_INGAME;

                if (menuAccion != nullptr)
                    delete menuAccion;

                // --- NUEVO: Menú dinámico al terminar de moverse ---
                claseTrabajo* trabajoAct = personajeSeleccionado->getTrabajo();
                int idC = (trabajoAct != nullptr) ? trabajoAct->getIdTrabajo() : 0;

                switch (idC)
                {
                case 1: // Arquero
                    menuAccion = new Menu(personajeSeleccionado->getPosxPxl() + 64, personajeSeleccionado->getPosyPxl(), {"Mover", "Disparar", "Esperar", "Cancelar"});
                    break;
                case 2: // Médico
                    menuAccion = new Menu(personajeSeleccionado->getPosxPxl() + 64, personajeSeleccionado->getPosyPxl(), {"Mover", "Curar", "Esperar", "Cancelar"});
                    break;
                default: // Guerrero o Default
                    menuAccion = new Menu(personajeSeleccionado->getPosxPxl() + 64, personajeSeleccionado->getPosyPxl(), {"Mover", "Atacar", "Esperar", "Cancelar"});
                    break;
                }

                personajeSeleccionado->setYaMovio(true);
            }
        }
        if(partida.getTurno() == 1)
        {
            if (!manager.moverpersonaje(persNJ[ia.getContIA()], movimiento.getCamino()))
            {
                persNJ[ia.getContIA()].setYaMovio(true);
                Estado = CURSOR_LIBRE;
            }
        }
    }

    if (partida.getTurno() == 0 && todasLasUnidadesActuaron(pers) && Estado == CURSOR_LIBRE)
    {
        partida.pasarTurno();
        resetearAccionesJugador(pers);
        movimiento.setEnemigos(&pers);
    }
    if (partida.getTurno() == 1 && todasLasUnidadesActuaron(persNJ) && Estado == CURSOR_LIBRE)
    {
        partida.pasarTurno();
        ia.resetContIA();
        resetearAccionesJugador(persNJ);
        movimiento.setEnemigos(&persNJ);
    }

    if (!persNJ.empty() && manager.contarPersonajesActivos(persNJ) == 0)
    {
        nivelSuperado = true;
    }
}
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
        case '2':
            tablero.setCelda(new DefaultCelda(i % tamFila, i / tamFila, 255, *texturas.getCelda(PICO)));
            i++;
            break;
        case '3':
            tablero.setCelda(new DefaultCelda(i % tamFila, i / tamFila, 255, *texturas.getCelda(PARED)));
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
        case ' ':
            tablero.setCelda(new CeldaTerrestre(i % tamFila, i / tamFila, 1, 0, *texturas.getCelda(PISO)));
            i++;
            break;
        default:
            i++;
        }
    }
    fclose(archMapa);
    return 0;
}

void Juego::renderizar(sf::RenderWindow &window)
{
    window.clear(sf::Color::Blue);

    tablero.render(window);

    manager.actualizarpersonaje(pers);
    manager.actualizarpersonaje(persNJ);
    manager.mostrarpersonaje(pers, window);
    manager.mostrarpersonaje(persNJ, window);
    animacion.mostrarvida(window, pers,1);
    animacion.mostrarvida(window, persNJ,2);
/*
    for (personaje &nose : persNJ)
        window.draw(nose.getsprite());
*/
    if (Estado == PREPARAR_ATAQUE)
    {
        // ACTUALIZADO: Nuevo parámetro del ataque agregado
        ataque.prepararataque(pers[manager.getactual()].getdireccion(), window, pers, persNJ, manager, ataque.getopciondeataque());
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

    if (Estado == SUBMENU_ATAQUES && menuSubOpciones != nullptr)
    {
        menuSubOpciones->draw(window);
    }

    if(Estado == ANIMACION_DAÑO)
    {
        bool van1 = animacion.mostraranimacion(window);
        bool van2;
        if(partida.getTurno() == 0)
        {
          van2 = animacion.mostrarataque(pers[manager.getactual()],window,ataque);
        }
        else if(partida.getTurno() == 1)
        {
          van2 = animacion.mostrarataque(persNJ[ia.getContIA()],window,ataque);
        }

        if(!van1&&!van2)
        {
            Estado = CURSOR_LIBRE;
        }
    }
    if (Estado == PAUSA && menuPausa != nullptr)
    {
        menuPausa->draw(window);
    }
    window.display();
}

personaje *Juego::GetPersonajeSeleccionado()
{
    for (unsigned int i = 0; i < pers.size(); i++)
    {
        if (pers[i].getPosx() == cursor.getXPos() && pers[i].getPosy() == cursor.getYPos() && pers[i].getHpReal() > 0)
        {
            manager.setActual(i);
            return &pers[i];
        }
    }
    return nullptr;
}

bool Juego::todasLasUnidadesActuaron(std::vector<personaje>& faccion)
{
    for (unsigned int i = 0; i < faccion.size(); i++)
    {
        if (faccion[i].getHpReal() != 0 && !faccion[i].getYaActuo())
            return false;
    }
    return true;
}

void Juego::resetearAccionesJugador(std::vector<personaje>& faccion)
{
    for (unsigned int i = 0; i < faccion.size(); i++)
    {
        faccion[i].setYaActuo(false);
        faccion[i].setYaMovio(false);
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

void Juego::SpawnPersonaje(const char *archivoPersonajes)
{
    AdminArchivo personajes(archivoPersonajes);
    int x, y, trabajo, maxHp, fuerza, defensa, err;
    const char separador = ';';

    err = personajes.abrir();
    if(err)
      std::cout << "Error abriendo personajesX.txt: " << err << std::endl;
    int cantPJ = personajes.leerNumero();

    for (int i = 0; i < cantPJ; i++)
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

    for (int i = 0; i < cantPNJ; i++)
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
    if(personajes.cerrar() != 0)
      std::cout << "no se cerro personajesX.txt" << std::endl;
}

void Juego::declararCuracion(vector<personaje>& propio, personaje *actual)
{
    animacion.asignaranimacion(propio, propio, ataque, manager);
    Estado = ANIMACION_DAÑO;
    cont = 0;

    for (int i = 0; i < ataque.getcantidadimpactos(); i++)
    {
        Combate combate(&tablero, actual, &propio[ataque.getimpactos()[i]]);
        combate.curacion();
    }
}

void Juego::declararAtaque(vector<personaje>& atk,vector<personaje>& def, personaje *actual)
{
    animacion.asignaranimacion(atk, def, ataque, manager);
    Estado = ANIMACION_DAÑO;
    cont = 0;

    for (int i = 0; i < ataque.getcantidadimpactos(); i++)
    {
        Combate combate(&tablero, actual, &def[ataque.getimpactos()[i]]);
        combate.pelea();
    }
}
