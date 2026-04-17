#include "defaultcelda.h"

DefaultCelda::DefaultCelda(int x, int y, int costo, sf::Texture &tex) : Celda(x, y, costo), sprite(tex) 
{
  sprite.setTexture(tex);
  return;
}

void DefaultCelda::render(sf::RenderWindow &window, int ladoCeldaEnPixeles)
{
  sprite.setPosition(sf::Vector2f(xPos * ladoCeldaEnPixeles, yPos * ladoCeldaEnPixeles));
  window.draw(sprite);
}

DefaultCelda::~DefaultCelda()
{

}
