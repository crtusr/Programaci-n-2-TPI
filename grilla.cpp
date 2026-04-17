#include "grilla.h"

Grilla::Grilla(int ladoCeldaEnPixeles, int xMaximo, int yMaximo)
{
  celda = nullptr;
  tamCeldaPixeles = ladoCeldaEnPixeles;
  maxX = xMaximo;
  maxY = yMaximo;
  celda = new Celda* [maxY * maxX];
  if(celda == nullptr)
  {
    maxX = 0;
    maxY = 0;
    return;
  }
  for(int i = 0; i < maxY * maxX; i++)
  {
    celda[i] = nullptr;
  }
  return;
}


int Grilla::getMaxX()
{
  return maxX;
}
int Grilla::getMaxY()
{
  return maxY;
}
int Grilla::getTamCeldaPixeles()
{
  return tamCeldaPixeles;
}
Celda* Grilla::getCelda(int x, int y)
{
  if(x >= maxX || y >= maxY)
    return nullptr;
  return celda[y * maxX + x];
}
void Grilla::setCelda(int x, int y, Celda* cel)
{
  if(x >= maxX || y >= maxY)
    return;
  celda[y * maxX + x] = cel;
  return;
}
void Grilla::render(sf::RenderWindow &window)
{
  for(int i = 0; i < (maxX * maxY); i++)
  {
    if(celda[i] == nullptr)
      continue;
    celda[i]->render(window, tamCeldaPixeles);
  }
}
Grilla::~Grilla()
{
  if(celda != nullptr)
  {
    for(int i = 0; i < (maxX * maxY); i++)
      if(celda[i] != nullptr)
        delete celda[i];
    delete [] celda;
  }
}
