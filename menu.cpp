#include "menu.h"
#include <iostream>

Menu::Menu(float x, float y, std::vector<std::string> opciones) {

if (!font.openFromFile("assets/fuente_pixel.otf")) {
    std::cout << "No se encontro la fuente!" << std::endl;
    exit(-1);        // Cierra el programa.
}
// Recorremos la lista de palabras que nos pasaron
    // Recorremos la lista de palabras que nos pasaron
    for (size_t i = 0; i < opciones.size(); i++) {
        // SFML 3 exige pasar la fuente, la palabra y el tamaño en el constructor:
        sf::Text texto(font, opciones[i], 30);

        // El primer elemento empieza en rojo (seleccionado), el resto en blanco
        if (i == 0) {
            texto.setFillColor(sf::Color::Red);
        } else {
            texto.setFillColor(sf::Color::White);
        }

        // Posicionamos cada texto un poco más abajo que el anterior (ej. 40 píxeles de separación)
        texto.setPosition(sf::Vector2f(x, y + (i * 40)));

        menu.push_back(texto); // Lo guardamos en el vector principal
    }
    selectedItemIndex = 0;
}

Menu::~Menu() {}

void Menu::draw(sf::RenderWindow &window) {
    // Recorremos el vector y dibujamos cada texto
    for (size_t i = 0; i < menu.size(); i++) {
        window.draw(menu[i]);
    }
}

void Menu::moveUp() {
    if (selectedItemIndex - 1 >= 0) {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void Menu::moveDown() {
    if (selectedItemIndex + 1 < (int)menu.size()) {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}
