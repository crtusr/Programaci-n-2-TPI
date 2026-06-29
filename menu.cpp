#include "menu.h"
#include <iostream>

Menu::Menu(float x, float y, std::vector<std::string> opciones) {

    if (!font.openFromFile("assets/fuente_pixel.otf")) {
        std::cout << "No se encontro la fuente!" << std::endl;
        exit(-1);
    }

    float anchoFondo = 0.0f;
    for (size_t i = 0; i < opciones.size(); i++) {
        sf::Text textoTemporal(font, opciones[i], 30);
        float anchoActual = textoTemporal.getLocalBounds().size.x;
        if (anchoActual > anchoFondo) anchoFondo = anchoActual;
    }
    anchoFondo += 80.0f;
    float altoFondo = opciones.size() * 40.0f + 20.0f;

    fondoPanel.setSize(sf::Vector2f(anchoFondo, altoFondo));
    fondoPanel.setOrigin(sf::Vector2f(anchoFondo / 2.0f, altoFondo / 2.0f));
    fondoPanel.setPosition(sf::Vector2f(x, y));
    fondoPanel.setFillColor(sf::Color(0, 0, 0, 200));
    fondoPanel.setOutlineColor(sf::Color::White);
    fondoPanel.setOutlineThickness(3);

    float alturaTotalTextos = (opciones.size() - 1) * 40.0f;
    float inicioY = y - (alturaTotalTextos / 2.0f) - 15.0f;

    for (size_t i = 0; i < opciones.size(); i++) {
        sf::Text texto(font, opciones[i], 30);

        if (i == 0) texto.setFillColor(sf::Color::Red);
        else texto.setFillColor(sf::Color::White);

        sf::FloatRect limitesTexto = texto.getLocalBounds();

        texto.setOrigin(sf::Vector2f(limitesTexto.position.x + limitesTexto.size.x / 2.0f, 0));
        texto.setPosition(sf::Vector2f(x, inicioY + (i * 40.0f)));

        menu.push_back(texto);
    }
    selectedItemIndex = 0;
}
Menu::~Menu() {}

void Menu::draw(sf::RenderWindow &window) {
    window.draw(fondoPanel);
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
