#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <SFML/Graphics.hpp>

#include <vector>
#include <string>

class Menu {
public:
    // El constructor recibe el tamaño de la ventana para centrar los textos
    Menu(float x, float y, std::vector<std::string> opciones);
    ~Menu();

    void draw(sf::RenderWindow &window);
    void moveUp();   // Para subir en las opciones
    void moveDown(); // Para bajar en las opciones

    // Nos devuelve qué opción está seleccionada (0, 1 o 2)
    int getPressedItem() { return selectedItemIndex; }

private:
    int selectedItemIndex; // Guarda el número de la opción resaltada
    sf::Font font;         // La fuente.
    std::vector<sf::Text> menu;
};

#endif // MENU_H_INCLUDED
