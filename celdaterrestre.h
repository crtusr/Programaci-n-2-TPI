#ifndef BOSQUECELDA_H
#define BOSQUECELDA_H

#include "celda.h"

/*
 * Esto representaria cualquier celda caminable, no le puse más atributos de
 * momento poero quizas se expanda.
 */

class CeldaTerrestre : public Celda
{
    private:
      int defensa;
      sf::Sprite sprite;
    public:
      CeldaTerrestre(int x, int y, int costo, int def, sf::Texture &tex);
      sf::Sprite getSprite();
      int getDefensa();
      void render(sf::RenderWindow &window, int ladoCeldaEnPixeles);
      ~CeldaTerrestre();
};

#endif
