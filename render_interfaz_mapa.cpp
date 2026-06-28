#include "render_interfaz_mapa.h"

RenderInterfazMapa::RenderInterfazMapa(Grilla *g) : 
  cursorTex("imagen/cursor.png"),
  cursorSprite(cursorTex)
{
  grilla = g;
  cuadradoTranslucido.setSize(sf::Vector2f(g->getTamCeldaPixeles(), g->getTamCeldaPixeles()));
}

void RenderInterfazMapa::renderRangoMovimiento(const bool *valido, sf::RenderWindow &win)
{
  cuadradoTranslucido.setFillColor(sf::Color(127, 127, 255, 127));
  cuadradoTranslucido.setPosition(sf::Vector2f(0,0));
  for(int y = 0; y < grilla->getMaxY(); y++)
  {
    for(int x = 0; x < grilla->getMaxX(); x++)
    {
      if(valido[x + (y * grilla->getMaxX())])
      {
        cuadradoTranslucido.setPosition
        (
          sf::Vector2f(x * grilla->getTamCeldaPixeles(),
                       y * grilla->getTamCeldaPixeles())
        );
        win.draw(cuadradoTranslucido);
      }
    }
  }
}
void RenderInterfazMapa::renderRangoAtaque()
{
  
}
void RenderInterfazMapa::renderCursor(CursorJuego curs, sf::RenderWindow &win)
{
  cursorSprite.setPosition(sf::Vector2f(curs.getXPos() * 64, curs.getYPos() * 64));
  win.draw(cursorSprite);

}
