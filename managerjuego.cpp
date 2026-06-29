#include "managerjuego.h"
#include "juego.h"

// EL CONSTRUCTOR
ManagerJuego::ManagerJuego() :
    window(sf::VideoMode({1024, 768}), "Project Tactics"),
    menuInicio(512, 384, {"Jugar", "Salir"})
{
    window.setFramerateLimit(60);
}

// EL MENÚ PRINCIPAL
// EL MENÚ PRINCIPAL
bool ManagerJuego::mostrarMenuPrincipal() {
    window.setView(window.getDefaultView());

    bool enMenu = true;
    int accionPendiente = -1; // -1 = Ninguna, 0 = Jugar, 1 = Salir

    if (animacion.estaEnTransicion() && animacion.getFrameTransicion() == 1000) {
        animacion.setFrameTransicion(2000);
    }

    while (window.isOpen() && enMenu) {

        // 1. EVENTOS
        if (!animacion.estaEnTransicion()) {
            while (const std::optional<sf::Event> event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>()) {
                    window.close();
                    return true;
                }
                else if (const auto *key = event->getIf<sf::Event::KeyPressed>()) {
                    if (key->code == sf::Keyboard::Key::Up) {
                        menuInicio.moveUp();
                    }
                    else if (key->code == sf::Keyboard::Key::Down) {
                        menuInicio.moveDown();
                    }
                    else if (key->code == sf::Keyboard::Key::Enter) {
                        int opcion = menuInicio.getPressedItem();
                        if (opcion == 0 || opcion == 1) {
                            accionPendiente = opcion;
                            animacion.iniciartrancicion();
                        }
                    }
                }
            }
        }

        // 2. DIBUJADO DEL FONDO Y MENÚ
        window.clear(sf::Color::Blue);
        menuInicio.draw(window);

        // 3. ACTUALIZACIÓN DE LA TRANSICIÓN
        if (animacion.estaEnTransicion()) {
            animacion.animartrancicion(window);

            // ¡CORRECCIÓN ACÁ!: Solo forzamos la pantalla negra si QUEREMOS SALIR
            // del menú (accionPendiente distinto de -1)
            if (accionPendiente != -1 && animacion.getFrameTransicion() >= 1000) {

                window.clear(sf::Color::Black);
                window.display();
                window.clear(sf::Color::Black);
                window.display();

                if (accionPendiente == 0) {
                    return false;
                }
                else if (accionPendiente == 1) {
                    window.close();
                    return true;
                }
            }
        }

        // 4. MOSTRAR EN PANTALLA
        window.display();
    }

    return false;
}

// CARGADOR DE NIVELES
bool ManagerJuego::cargarPartida(const char* archivoMapa, const char* archivoPersonajes)
{
    Juego nivelActual(archivoMapa, archivoPersonajes);
    bool jugadorGano = nivelActual.ejecutar(window);
    return jugadorGano;
}
