#ifndef SISMOV_H
  #define SISMOV_H

  #include "grilla.h"
  /*
   * El objetivo de esta clase es calcular en una matriz de booleanos todas las
   * casillas que son validas para moverse por una unidad en las coordenadas x y
   * de la grilla.
   */
  
  class SisMov
  {
    private:
      int xPos;
      int yPos;
      int bordeDerecho;
      int bordeInferior;
      Grilla *grid;
      bool *valido;
    public:
      SisMov(int x, int y, Grilla *g);
      void resetValido();
      void movRango(int x, int y, int mov);
      bool *getValido();
      ~SisMov();
  }; 

#endif
