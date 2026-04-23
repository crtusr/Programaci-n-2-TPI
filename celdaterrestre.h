#ifndef BOSQUECELDA_H
#define BOSQUECELDA_H

#include "celda.h"

class CeldaTerrestre : public Celda
{
    private:
      int defensa;
      sf::Sprite sprite;
    public:
      CeldaTerrestre(int x, int y, int costo, sf::Texture &tex);
      sf::Sprite getSprite();
      int getDefensa();
      void render(sf::RenderWindow &window, int ladoCeldaEnPixeles);
      ~CeldaTerrestre();
};

#endif
