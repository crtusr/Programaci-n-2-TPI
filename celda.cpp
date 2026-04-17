#include "celda.h"

Celda::Celda(int x, int y, int costo)
{
  xPos = x;
  yPos = y;
  costoMov = costo;
}
int Celda::getXPos()
{
  return xPos;
}
int Celda::getYPos()
{
  return yPos;
}
int Celda::getCostoMov()
{
  return costoMov;
}
void Celda::setXPos(int posXGrilla)
{
  xPos = posXGrilla;
}
void Celda::setYPos(int posYGrilla)
{
  yPos = posYGrilla;
}
void Celda::setCostoMov(int costo)
{
  costoMov = costo;
}
Celda::~Celda()
{

}
