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
    tablero(64, 15, 10),
    rendUi(&tablero),
    pers(5, personaje(&tablero)),
    movimiento(0, 0, &tablero)
{
    window.setFramerateLimit(60);

    square.setSize(sf::Vector2f(64,64));
    square.setFillColor(sf::Color(127, 127, 255, 127));
    teclaPresionada = 0;
    cargarTexturasDeCeldas();
    cargarMapa("nivel1.txt");

    //---declaro estos vectores pero se tendrian que obtener de puntos de repawn
int tipo[10]={1,1,1,1,1,1,1,1,1,1}; //estos son los tipos de personaje que se asignaran
int cantidaddepersonajes = 5;
int posinicialx[10]={};             //estos vectores los tiene que proporcionar el inicio de mapa
int posinicialy[10]={64*2,64*3,64*4,64*5,64*6};
manager.setcantidad(cantidaddepersonajes);            //
    for(int i = 0; i < cantidaddepersonajes; i++) {
        manager.Asignarpersonajes(pers[i],tipo[i],posinicialx[i],posinicialy[i]);
        }
    
    Estado = CURSOR_LIBRE;

    personajeSeleccionado = nullptr;

    for (int i = 0; i < 5; i++) {
        pers[i].yaActuo = false;
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
                if ( Estado == PERSONAJE_SELECCIONADO) {
                    if(teclaPresionada == ENTER) {
                        movimiento.setDestino(cursor.getXPos(), cursor.getYPos());
                        if (!movimiento.Alcanzable(cursor.getXPos(), cursor.getYPos())) {
                            Estado = CURSOR_LIBRE;
                            teclaPresionada = NULO;
                            personajeSeleccionado = nullptr;
                            return;
                        }
                        else {
                            movimiento.buscarCamino(personajeSeleccionado->getPosx(), personajeSeleccionado->getPosy(), mov);
                            manager.resetCaminoIndice();
                            Estado = ANIMACION_BLOQUEANTE;
                            //  manager.mostrarpersonaje(*personajeSeleccionado, window);
                            //moverPersonajeSeleccionado();
                        }
                    }
                    else if(key->code == sf::Keyboard::Key::A) { mov++; }
                    else if(key->code == sf::Keyboard::Key::S) { mov--; }
                }
                if (Estado == CURSOR_LIBRE && teclaPresionada == ENTER) 
                {
                    personaje* P = GetPersonajeSeleccionado();
                    if (P != nullptr && !P->yaActuo) 
                    {
                        personajeSeleccionado = P;
                        Estado = PERSONAJE_SELECCIONADO;
                        teclaPresionada = NULO;
                        movimiento.calcularMovimiento(P->getPosx(), P->getPosy(), mov);
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


                    if(teclaPresionada == F && (!pers[manager.getactual()].getblockaccion()))
                    {
                      Estado=PREPARAR_ATAQUE;
                    }
                }
                else if(Estado == PREPARAR_ATAQUE)
                {
                    manager.cambiardireccion(pers, teclaPresionada);
                    ataque.prepararataque(pers[manager.getactual()].getdireccion(),window,pers,manager);
                    if((teclaPresionada == SPACE)&&(!pers[manager.getactual()].getblockaccion()))
                    {
                        Estado=CURSOR_LIBRE;
                    }
                    if(teclaPresionada == F && (!pers[manager.getactual()].getblockaccion()))
                    {
                        Estado=CURSOR_LIBRE;
                    }
                }
                teclaPresionada = NULO;
            }
        }
    }
}


// ACTUALIZAR: Integraci�n total del Manager y Personajes.
void Juego::actualizar() 
{
  cout << Estado << "\n";
  if (enMenu)
    return;
  if (Estado == CURSOR_LIBRE)
  {
      manager.moverpersonaje(pers[manager.getactual()]);
      manager.cambiarpersonaje(pers[manager.getactual()]);
  }
  if(Estado==PREPARAR_ATAQUE)
  {
  }

  manager.actualizarpersonaje(pers);
  if(Estado == ANIMACION_BLOQUEANTE)
  {
    if(!manager.moverpersonaje(*personajeSeleccionado, movimiento.getCamino()))
    {
      Estado = CURSOR_LIBRE;
      personajeSeleccionado->yaActuo = (true);
    }
  }
  if (todasLasUnidadesActuaron()) 
  {
    partida.pasarTurno();
    resetearAccionesJugador();
  }
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

    // Renderizamos los 5 personajes del equipo tal como ped�a el main viejo
    manager.actualizarpersonaje(pers);
    manager.mostrarpersonaje(pers, window);

    if(Estado == CURSOR_LIBRE || Estado == PERSONAJE_SELECCIONADO)
      rendUi.renderCursor(cursor, window);
    if (Estado == PERSONAJE_SELECCIONADO) 
    {
      rendUi.renderRangoMovimiento(movimiento.getValido(), window);
    }
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
            case '0': tablero.setCelda(new DefaultCelda(i % tamFila, i / tamFila, 255, texCelda[DEFAULT])); i++; break;
            case 'P': tablero.setCelda(new CeldaTerrestre(i % tamFila, i / tamFila, 1, 1, texCelda[PRADO])); i++; break;
            case 'B': tablero.setCelda(new CeldaTerrestre(i % tamFila, i / tamFila, 2, 2, texCelda[BOSQUE])); i++; break;
            case 'M': tablero.setCelda(new CeldaTerrestre(i % tamFila, i / tamFila, 4, 3, texCelda[MONTANIA])); i++; break;
            default: i++;
        }
    }
    fclose(archMapa);
    return 0;
}


personaje* Juego::GetPersonajeSeleccionado() {
    for (int i = 0; i < pers.size(); i++) {
        if (pers[i].getPosx() == cursor.getXPos() && pers[i].getPosy() == cursor.getYPos()) {
            return &pers[i];
        }
    }
    return nullptr; // Placeholder para compilar
}
    bool Juego::todasLasUnidadesActuaron() {
    for (int i = 0; i < pers.size(); i++) {
        if (!pers[i].yaActuo) {
            return false;
        }
    }
    return true;
}

    void Juego::resetearAccionesJugador() {
    for (int i = 0; i < pers.size(); i++) {
        pers[i].yaActuo = false;
    }
}

void Juego::moverPersonajeSeleccionado()
{
  if (personajeSeleccionado == nullptr) 
    return;
  const int* camino = movimiento.getCamino();
  int x = personajeSeleccionado->getPosx();
  int y = personajeSeleccionado->getPosy();
  for(int i = 0; i < profundidadMax && camino[i] != -1; i++) 
  {
    switch(camino[i]) 
    {
      case ARRIBA: y -= 1; break;
      case ABAJO: y += 1; break;
      case IZQUIERDA: x -= 1; break;
      case DERECHA: x += 1; break;    
    }
  }
  personajeSeleccionado->setposx(x * 64);
  personajeSeleccionado->setposy(y * 64);
  personajeSeleccionado->setsprite(1);
  personajeSeleccionado->yaActuo = true;
  Estado = CURSOR_LIBRE;
  for(int i = 0; i < 5; i++) 
    cout << endl << pers[i].getPosxPxl() << " " << pers[i].getPosyPxl();
  personajeSeleccionado = nullptr;
}

