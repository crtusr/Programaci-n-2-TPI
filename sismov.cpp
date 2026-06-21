#include "grilla.h"
#include "sismov.h"
#include "constantes.h"
#include <cstdlib>
#include <iostream>
#include "managerpersonaje.h"

SisMov::SisMov(int x, int y, Grilla *g, std::vector<personaje>& e) : enemigos(e)
{
  enemigos = e;
  xPos = x;
  yPos = y;
  grid = g;
  bordeDerecho = grid->getMaxX();
  bordeInferior = grid->getMaxY();
  valido = new bool[grid->getMaxX() * grid->getMaxY()];
  if(valido == nullptr)
  {
    bordeDerecho = 0;
    bordeInferior = 0;
  }
}

void SisMov::resizeGrid(Grilla *g)
{
  if(valido != nullptr)
    delete [] valido;
  bordeDerecho = g->getMaxX();
  bordeInferior = g->getMaxY();
  valido = new bool[g->getMaxX() * g->getMaxY()];
}
void SisMov::setDestino(int x, int y)
{
  xPos = x;
  yPos = y;
  return;
}

void SisMov::setEnemigos(std::vector<personaje>& e)
{
  enemigos = e;
}

/*  Este metodo pone toda la grilla de booleanos en false como para poder usar
 *  el rango de movimiento en otro personaje
 */
void SisMov::resetValido()
{
  for(int i = 0; i < grid->getMaxX() * grid->getMaxY(); i++)
    valido[i] = false;
}

/*
 * Esto es lo que se llama un algoritmo recursivo que usa DFS busqueda en
 * profundidad (Depth-first Search) que recorre Exaustivamente todos los caminos
 * posibles. Es un algoritmo recursivo porque en vez de usar un ciclo for o
 * while usa la propia llamada de la función para iterar, tiene la ventaja que
 * te permite iteraciónes más elegantes (pero que pueden dificultar el control
 * de flujo). En este caso en particular facilita el entendimiento porque si se
 * quisiera hacer con un ciclo while o for habria que tambien implementar una
 * estructura de datos que es una pila, acá la pila te la brinda la propia
 * recursión.
 *
 * ej:
 *  int funcion(a)
 *  {
 *    if(a <= 0)
 *      return 0;
 *    else
 *      return a + funcion(a - 1);
 *  }
 *
 *  Esto se llama a si mismo mientras a > 0, y funcion(a) devolverá la sumatoria
 *  de 1 hasta a.
 *
 *  en el caso de movRango la llamo para todas las direcciónes, pero primero va
 *  a agotar todo el movimiento en reevaluar la función en y+1 (hacia abajo)
 *  cuando se queda sin la función retorna pero en el lugar donde fue llamada
 *  esa función y el movimiento "rebobina" al valor de la llamada anterior
 *  (porque cada llamada) tiene su propio scope con su propio stack. Despues
 *  prueba en las subsiguientes funciones, hasta esplotar todos los posibles
 *  caminos que se podrian hacer con la cantidad de movimiento inicial.
 */

bool SisMov::hayNumeroDistinto(int low, int high)
{
  for(int i = low; i < high; i++)
  {
    if(camino[i] != camino[low] && camino[i] != camino[high] && camino[i])
      return true;
  }
  return false;
}

int SisMov::calcDistCamino(int low, int high)
{
  int distancia = 0;
  for(int i = low + 1; i < high; i++)
    if(camino[i])
      distancia++;
  return distancia;
}

void SisMov::achicarCamino()
{
  int i = 0, j = 0;
  while(i < profundidadMax && camino[i] != -1)
    i++;
  for(int diff = 1; diff < i; diff++)
  { 
    j = 0;
    while(j + diff < i)
    {
      if(abs(camino[j] - camino[j + diff]) == 2)
      {
        if(calcDistCamino(j, j + diff) <= 2)
        {
          camino[j] = 0;
          camino[j + diff] = 0;
        }
        else if(!hayNumeroDistinto(j ,j + diff))
        {
          camino[j] = 0;
          camino[j + diff] = 0;
        }
      }
      j++;
    }
  }
}

bool SisMov::buscarCaminoPriv(int x, int y, int mov, int profundidad)
{
    if(x == xPos && y == yPos)
    {
      return true;
    }
    if(profundidad == profundidadMax || mov < 0)
    {
      return false;
    }
    //si facilitan la lectura XD, lo copie pegue no mas esta parte
    int costoCeldaInferior = y+1 < bordeInferior ? grid->getCelda(x, y + 1)->getCostoMov() : 255;
    int costoCeldaIzquierda = x-1 >= 0 ? grid->getCelda(x - 1 , y)->getCostoMov() : 255;
    int costoCeldaSuperior = y-1 >= 0 ? grid->getCelda(x, y - 1)->getCostoMov() : 255;
    int costoCeldaDerecha = x+1 < bordeDerecho ? grid->getCelda(x + 1, y)->getCostoMov() : 255;
    camino[profundidad] = -1;
    if(y + 1 < bordeInferior && mov >= costoCeldaInferior)
    {
      if(managerpersonaje::comprobarLugarTablero(x , y + 1, enemigos) == -1)
      {
        camino[profundidad] = ABAJO;
        if(buscarCaminoPriv(x, y + 1, mov - costoCeldaInferior, profundidad + 1))
          return true;
      }
    }
    if(x - 1 >= 0 && mov >= costoCeldaIzquierda)
    {
      if(managerpersonaje::comprobarLugarTablero(x - 1 , y, enemigos) == -1)
      {
        camino[profundidad] = IZQUIERDA;
        if(buscarCaminoPriv(x - 1 , y, mov - costoCeldaIzquierda, profundidad + 1))
          return true;
      }
    }
    if(y - 1 >= 0 && mov >= costoCeldaSuperior)
    {
      if(managerpersonaje::comprobarLugarTablero(x, y - 1, enemigos) == -1)
      {
        camino[profundidad] = ARRIBA;
        if(buscarCaminoPriv(x, y - 1, mov - costoCeldaSuperior, profundidad + 1))
          return true;
      }
    }
    if(x + 1 < bordeDerecho && mov >= costoCeldaDerecha)
    {
      if(managerpersonaje::comprobarLugarTablero(x + 1 , y, enemigos) == -1)
      {
        camino[profundidad] = DERECHA;
        if(buscarCaminoPriv(x + 1, y, mov - costoCeldaDerecha, profundidad + 1))
          return true;
      }
    }
    camino[profundidad] = -1;
    return false;
}

void SisMov::buscarCamino(int x, int y, int mov)
{
  resetCamino();
  if(!valido[xPos + (yPos * bordeDerecho)])
  {
    return;
  }
  buscarCaminoPriv(x, y, mov, 0);
  system("cls");
  std::cout << "Camino: ";
  for(int i = 0; i < profundidadMax; i++)
  {
    std::cout << camino[i] << " ";
  }
  std::cout << std::endl;
  achicarCamino();
  std::cout << "Camino: ";
  for(int i = 0; i < profundidadMax; i++)
  {
    std::cout << camino[i] << " ";
  }
  std::cout << std::endl;
}

void SisMov::movRango(int x, int y, int mov)
{
  /*estas 4 variables las hice simplemente para facilitar la lectura del algoritmo*/
  int costoCeldaInferior = y+1 < bordeInferior ? grid->getCelda(x, y + 1)->getCostoMov() : 255;
  int costoCeldaIzquierda = x-1 >= 0 ? grid->getCelda(x - 1 , y)->getCostoMov() : 255;
  int costoCeldaSuperior = y-1 >= 0 ? grid->getCelda(x, y - 1)->getCostoMov() : 255;
  int costoCeldaDerecha = x+1 < bordeDerecho ? grid->getCelda(x + 1, y)->getCostoMov() : 255;

  if(!valido[x + (y * bordeDerecho)])
  {
    valido[x + (y * bordeDerecho)] = true;
  }
  if(y + 1 < bordeInferior && mov >= costoCeldaInferior)
    if(managerpersonaje::comprobarLugarTablero(x , y + 1, enemigos) == -1)
      movRango(x, y + 1, mov - costoCeldaInferior);
  if(x - 1 >= 0 && mov >= costoCeldaIzquierda)
    if(managerpersonaje::comprobarLugarTablero(x - 1 , y, enemigos) == -1)
      movRango(x - 1 , y, mov - costoCeldaIzquierda);
  if(y - 1 >= 0 && mov >= costoCeldaSuperior)
    if(managerpersonaje::comprobarLugarTablero(x , y - 1, enemigos) == -1)
      movRango(x, y - 1, mov - costoCeldaSuperior);
  if(x + 1 < bordeDerecho && mov >= costoCeldaDerecha)
    if(managerpersonaje::comprobarLugarTablero(x + 1 , y, enemigos) == -1)
      movRango(x + 1, y, mov - costoCeldaDerecha);
}

void SisMov::calcularMovimiento(int x, int y, int mov)
{
  resetValido();
  if(x >= 0 && y >= 0 && x < bordeDerecho && y < bordeInferior)
    movRango(x, y, mov);
}
/*
 *  Lo pensé de manera que pudiera retornar el puntero a la grilla completa y
 *  se pueda llamar a la función que dibuja
 */
const bool *SisMov::getValido()
{
  return valido;
}

void SisMov::resetCamino()
{
  for(int i = 0; i < 16; i++)
  {
    camino[i] = -1;
  }
}

/*
 *  el array/matriz valido fue declarado de manera dinamica en el constructor
 *  asi que el destructor tendria que liberar la memoria alojada.
 */
SisMov::~SisMov()
{
  delete [] valido;
}
const int* SisMov::getCamino()
{
  return camino;
}
bool SisMov::Alcanzable(int x, int y){
  if(x < 0 || y < 0 || x >= bordeDerecho || y >= bordeInferior) {
    return false;
  }
  return valido[y*bordeDerecho + x];
}
