#include "celdaterrestre.h"

CeldaTerrestre::CeldaTerrestre(int x, int y, int costo, sf::Texture &tex) : Celda(x, y, costo), sprite(tex) 
{
  defensa = 2;
  sprite.setTexture(tex);
  return;
}

void CeldaTerrestre::render(sf::RenderWindow &window, int ladoCeldaEnPixeles)
{
  sprite.setPosition(sf::Vector2f(xPos * ladoCeldaEnPixeles, yPos * ladoCeldaEnPixeles));
  window.draw(sprite);
}

CeldaTerrestre::~CeldaTerrestre()
{

}
