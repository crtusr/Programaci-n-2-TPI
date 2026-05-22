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

int Grilla::getCantCeldas()
{
  return maxX * maxY;
}

/*se asume que las celdas son cuadradas... */
int Grilla::getTamCeldaPixeles()
{
  return tamCeldaPixeles;
}

/*
 * con este getter podes pedir la celda y simultaneamente usar los metodos de
 * la celda girlla.getCelda(x, y).metodoDeLaCelda().
 */
Celda* Grilla::getCelda(int x, int y)
{
  if(x >= maxX || y >= maxY)
    return nullptr;
  return celda[y * maxX + x];
}

/* Como cel es un puntero a una celda generica se declara dentro de los
 * parentesis un new (clase polimorfica heredada de celda), new devuelve una
 * dirección de memoria que va a ser el parametro pasado que tiene el tamaño
 * de la clase heredada. Celda en grilla se declaro como Celda** debido a eso
 * celda[x + y * maxX] te da un puntero, que con new se va a setear a la 
 * dirección del heap donde haya espacio para la clase hija. Por eso use esa
 * notación para la matriz en vez de la estandar celda[y][x], sino tendria que
 * haber declarado celda como Celda***.
 */
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

/*
 * Esta función manda a window (que entiendo que es el buffer de la ventana que
 * se renderiza).
 */
void Grilla::render(sf::RenderWindow &window)
{
  for(int i = 0; i < (maxX * maxY); i++)
  {
    if(celda[i] == nullptr)
      continue;
    celda[i]->render(window, tamCeldaPixeles);
  }
}


/*
 * Es el destructor necesario para liberar la memoria dinamica una vez que se 
 * dejan de usar las celdas (por ej. si se termina la partida)
 */
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
