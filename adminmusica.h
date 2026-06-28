#ifndef ADMIN_MUSICA_H
#define ADMIN_MUSICA_H

#include<SFML/Audio.hpp>

class AdminMusica
{
  private:
    sf::Music jugadores, enemigos;
    int errCode;
  public:
    AdminMusica(const char* player, const char *npc);
    void reproducirTemaJugadores();
    void reproducirTemaEnemigos();
    int getError();
};


#endif
