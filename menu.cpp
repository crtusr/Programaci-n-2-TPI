#include "menu.h"
#include <iostream>

Menu::Menu(float width, float height) {

if (!font.openFromFile("assets/fuente_pixel.otf")) {
    std::cout << "No se encontro la fuente!" << std::endl;
    exit(-1);        // Cierra el programa.
}
    sf::Text text1(font, "Jugar", 30);
    text1.setFillColor(sf::Color::Red);
    text1.setPosition(sf::Vector2f(width / 2 - 50, height / 4 * 1));
    menu.push_back(text1); // Lo guardamos en el vector

    sf::Text text2(font, "Opciones", 30);
    text2.setFillColor(sf::Color::White);
    text2.setPosition(sf::Vector2f(width / 2 - 70, height / 4 * 2));
    menu.push_back(text2);

    sf::Text text3(font, "Salir", 30);
    text3.setFillColor(sf::Color::White);
    text3.setPosition(sf::Vector2f(width / 2 - 40, height / 4 * 3));
    menu.push_back(text3);

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
