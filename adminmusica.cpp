#include "adminmusica.h"


AdminMusica::AdminMusica(const char* player, const char *npc)
{
  if(!jugadores.openFromFile(player))
    errCode = 1;
  if(!enemigos.openFromFile(npc))
    errCode = 2;
  jugadores.setLooping(true);
  enemigos.setLooping(true);
}
void AdminMusica::reproducirTemaJugadores()
{
  enemigos.stop();
  jugadores.play();

}
void AdminMusica::reproducirTemaEnemigos()
{

  jugadores.stop();
  enemigos.play();
}

int AdminMusica::getError()
{
  return errCode;
}
