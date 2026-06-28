#include "menu.h"
#include <iostream>

Menu::Menu(float x, float y, std::vector<std::string> opciones) {

    if (!font.openFromFile("assets/fuente_pixel.otf")) {
        std::cout << "No se encontro la fuente!" << std::endl;
        exit(-1);        // Cierra el programa.
    }

    // 1. Configuración de la ventana de fondo DINÁMICA
    // --- Calculamos el ancho dinámico según la palabra más larga ---
    float anchoFondo = 0.0f;
    for (size_t i = 0; i < opciones.size(); i++) {
        // Creamos un texto temporal solo para medirlo
        sf::Text textoTemporal(font, opciones[i], 30);
        float anchoActual = textoTemporal.getLocalBounds().size.x;

        // Si esta palabra es más ancha que las anteriores, guardamos su tamaño.
        if (anchoActual > anchoFondo) {
            anchoFondo = anchoActual;
        }
    }
    // Le sumamos 80 píxeles extra para que el texto tenga margen y no toque el borde.
    anchoFondo += 80.0f;
    // ---------------------------------------------------------------
    float altoFondo = opciones.size() * 40.0f + 20.0f;

    fondoPanel.setSize(sf::Vector2f(anchoFondo, altoFondo));
    fondoPanel.setOrigin(sf::Vector2f(anchoFondo / 2.0f, altoFondo / 2.0f));
    fondoPanel.setPosition(sf::Vector2f(x, y));
    fondoPanel.setFillColor(sf::Color(0, 0, 0, 200));
    fondoPanel.setOutlineColor(sf::Color::White);
    fondoPanel.setOutlineThickness(3);

    // 2. Calculamos dónde debe empezar el primer texto para que el bloque quede centrado.
    float alturaTotalTextos = (opciones.size() - 1) * 40.0f;
    float inicioY = y - (alturaTotalTextos / 2.0f);

    // 3. Recorremos la lista de palabras
    for (size_t i = 0; i < opciones.size(); i++) {
        sf::Text texto(font, opciones[i], 30);

        if (i == 0) {
            texto.setFillColor(sf::Color::Red);
        } else {
            texto.setFillColor(sf::Color::White);
        }

        // Centramos el origen exacto de cada palabra
        sf::FloatRect limitesTexto = texto.getLocalBounds();
        texto.setOrigin(sf::Vector2f(limitesTexto.position.x + limitesTexto.size.x / 2.0f, limitesTexto.position.y + limitesTexto.size.y / 2.0f));

        // Como el origen de la palabra está en su centro, le pasamos directamente x.
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
