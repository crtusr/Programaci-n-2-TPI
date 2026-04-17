#ifndef CELDA_H
#define CELDA_H

  #include <SFML/Graphics.hpp>
  #include <SFML/Window.hpp>
  class Celda
  {
    protected:
      int xPos;
      int yPos;
      int costoMov;
    public:
      Celda(int x, int y, int costo);
      int getXPos();
      int getYPos();
      int getCostoMov();
      void setXPos(int posXGrilla);
      void setYPos(int posYGrilla);
      void setCostoMov(int costo);
      virtual void render(sf::RenderWindow &window, int LadoCeldaEnPixeles) = 0;
      virtual ~Celda() = 0;
  };

#endif
