#include "grilla.h"

/*
 *  Sobre la "matriz" la matriz[Y][X] es en realidad una abrebiatura de [Y * maxX + X]
 *  y hacer eso te saca un * de la declaración, porque para implementar 
 *  polimorfismo si quería hacer una matriz variable (que necesiata usar new)
 *  tendria que haber declarado el puntero celda como Celda ***celda y hubiese 
 *  sido confuso. haciendo [Y * maxX + X] se puede sacar la posición X Y de la
 *  matriz.
 */

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

/*se asume que las celdas son cuadradas... */
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

/* Como cel es ta un puntero a una celda */
void Grilla::setCelda(Celda* cel)
{
  int x = cel->getXPos();
  int y = cel->getYPos();
  if(x >= maxX || y >= maxY)
    return;
  if(celda[y * maxX + x] != nullptr)
    delete celda[y * maxX + x];
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
