#include "managerjuego.h"
#include "juego.h"

// EL CONSTRUCTOR
ManagerJuego::ManagerJuego() :
    window(sf::VideoMode({1024, 768}), "Project Tactics"),
    menuInicio(450, 250, {"Jugar", "Opciones", "Salir"})
{
    window.setFramerateLimit(60);
}

// EL MENÚ PRINCIPAL
bool ManagerJuego::mostrarMenuPrincipal() {
    bool enMenu = true;
    bool quiereSalirDelJuego = false;

    while (window.isOpen() && enMenu) {

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

                    if (opcion == 0) {
                        enMenu = false;
                    }
                    else if (opcion == 2) {
                        window.close();
                        quiereSalirDelJuego = true;
                        enMenu = false;
                    }
                }
            }
        }

        window.clear(sf::Color::Blue);
        menuInicio.draw(window);
        window.display();
    }

    return quiereSalirDelJuego;
}

// CARGADOR DE NIVELES
bool ManagerJuego::cargarPartida(const char* archivoMapa, const char* archivoPersonajes) {
    Juego nivelActual(archivoMapa, archivoPersonajes);
    bool jugadorGano = nivelActual.ejecutar(window);
    return jugadorGano;
}
