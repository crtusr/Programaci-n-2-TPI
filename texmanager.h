#ifndef TEXMANAGER_H
#define TEXMANAGER_H
#include "SFML/Graphics.hpp"

  class TexManager
  {
    private:
      sf::Texture celda[10];
      sf::Texture personaje[10];
    public:
      TexManager(const char *archivos);
      sf::Texture *getPersonaje(int num);
      sf::Texture *getCelda(int num);
  };

#endif
