#include"cursor.h"
#include"constantes.h"

Cursor::Cursor(int x, int y)
{
  xPos = x;
  yPos = y;
}
int Cursor::getXPos()
{
  return xPos;
}
int Cursor::getYPos()
{
  return yPos;
}
void Cursor::setPos(int x, int y)
{
  xPos = x;
  yPos = y;
}
void Cursor::mover(int dir)
{
  switch(dir)
  {
    case ARRIBA:
      yPos--;
      break;
    case ABAJO:
      yPos++;
      break;
    case IZQUIERDA:
      xPos--;
      break;
    case DERECHA:
      xPos++;
      break;
    case ARRIBA_IZQUIERDA:
      xPos--;
      yPos--;
      break;
    case ARRIBA_DERECHA:
      xPos++;
      yPos--;
      break;
    case ABAJO_IZQUIERDA:
      xPos--;
      yPos++;
      break;
    case ABAJO_DERECHA:
      xPos++;
      yPos++;
      break;
  }
  return;
}
