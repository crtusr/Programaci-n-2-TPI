#ifndef GRILLA_H
#define GRILLA_H

  #include "celda.h"
  class Grilla
  {
    private:
      int tamCeldaPixeles; //se asume que las celdas son cuadradas
      int maxX;
      int maxY;
      Celda **celda;
    public:
      Grilla(int ladoCeldaEnPixeles = 0, int xMaximo = 0, int yMaximo = 0);
      int getMaxX();
      int getMaxY();
      int getTamCeldaPixeles();
      Celda* getCelda(int x, int y);
      void setCelda(int x, int y, Celda* cel);
      void render(sf::RenderWindow &window);
      ~Grilla();
  };

#endif
