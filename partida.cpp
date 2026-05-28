#include"partida.h"
Partida::Partida(int r, int t)
{
  ronda = r;
  turno = t;
}
int Partida::getRonda()
{
  return ronda;
}
int Partida::getTurno()
{
  return turno;
}
void Partida::pasarTurno()
{
  if(turno == 1)
    ronda++;
  turno ^= 1;
  return;
  /*
   * turno empieza en 0, al hacerle XOR, tambien conocido como OR exclusivo va
   * a oscilar entre los dos numeros 0 y 1, porque 0 ^ 1 = 1 y 1 ^ 1 = 0.
   */
}
