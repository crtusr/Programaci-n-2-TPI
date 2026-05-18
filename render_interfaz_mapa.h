#ifndef RENDER_INTERFAZ_MAPA
#define RENDER_INTERFAZ_MAPA

#include"grilla.h"
#include<SFML/Graphics.hpp>

class RenderInterfazMapa
{
  private:
    Grilla *grilla;
    sf::RectangleShape cuadradoTranslucido;

  public:
    RenderInterfazMapa(Grilla *g);
    void renderRangoMovimiento(bool *valido);
    void renderRangoAtaque();
    void renderCursor();
};

#endif
