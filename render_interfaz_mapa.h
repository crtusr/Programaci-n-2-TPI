#ifndef RENDER_INTERFAZ_MAPA
#define RENDER_INTERFAZ_MAPA

#include"grilla.h"
#include<SFML/Graphics.hpp>
#include "cursor.h"

class RenderInterfazMapa
{
  private:
    Grilla *grilla;
    sf::RectangleShape cuadradoTranslucido;
    sf::Texture cursorTex;
    sf::Sprite cursorSprite;

  public:
    RenderInterfazMapa(Grilla *g);
    void renderRangoMovimiento(const bool *valido, sf::RenderWindow &win);
    void renderRangoAtaque();
    void renderCursor(CursorJuego curs, sf::RenderWindow &win);
};

#endif
