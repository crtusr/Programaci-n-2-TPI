#include "grilla.h"
#include "sismov.h"

SisMov::SisMov(int x, int y, Grilla *g)
{
  xPos = x;
  yPos = y;
  grid = g;
  bordeDerecho = grid->getMaxX();
  bordeInferior = grid->getMaxY();
  valido = new bool[grid->getMaxX() * grid->getMaxY()];
}
void SisMov::resetValido()
{
  for(int i = 0; i < grid->getMaxX() * grid->getMaxY(); i++)
    valido[i] = false;
}
void SisMov::movRango(int x, int y, int mov)
{
  /*estas 4 variables las hice simplemente para facilitar la lectura del algoritmo*/
  int costoCeldaInferior = y+1 < bordeInferior ? grid->getCelda(x, y + 1)->getCostoMov() : 255;
  int costoCeldaIzquierda = x-1 >= 0 ? grid->getCelda(x - 1 , y)->getCostoMov() : 255;
  int costoCeldaSuperior = y-1 >= 0 ? grid->getCelda(x - 1 , y)->getCostoMov() : 255;
  int costoCeldaDerecha = x+1 < bordeDerecho ? grid->getCelda(x + 1, y)->getCostoMov() : 255;
  if(!valido[x + (y * bordeDerecho)])
  {
    valido[x + (y * bordeDerecho)] = true;
  }
  if(y + 1 < bordeInferior && mov >= costoCeldaInferior)
    movRango(x, y + 1, mov - costoCeldaInferior);
  if(x - 1 >= 0 && mov >= costoCeldaIzquierda)
    movRango(x - 1 , y, mov - costoCeldaIzquierda);
  if(y - 1 >= 0 && mov >= costoCeldaSuperior)
    movRango(x, y - 1, mov - costoCeldaSuperior);
  if(x + 1 < bordeDerecho && mov >= costoCeldaDerecha)
    movRango(x + 1, y, mov - costoCeldaDerecha);
}
bool *SisMov::getValido()
{
  return valido;
}
SisMov::~SisMov()
{
  delete [] valido;
}
