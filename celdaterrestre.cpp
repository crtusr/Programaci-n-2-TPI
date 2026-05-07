#include "celdaterrestre.h"

CeldaTerrestre::CeldaTerrestre(int x, int y, int costo, int def, sf::Texture &tex) : Celda(x, y, costo), sprite(tex) 
{
  defensa = def;
  sprite.setTexture(tex); // lo que se dibuja por pantalla es el sprite, a los que le cargo las texturas
  return;
}

void CeldaTerrestre::render(sf::RenderWindow &window, int ladoCeldaEnPixeles)
{
  /* Acá solo abstraje el hecho de calcular el renderizado manualmente y
   * y abstraigo el calculo de pixeles individuales
   */
  sprite.setPosition(sf::Vector2f(xPos * ladoCeldaEnPixeles, yPos * ladoCeldaEnPixeles));
  window.draw(sprite);
}

CeldaTerrestre::~CeldaTerrestre()
{

}
