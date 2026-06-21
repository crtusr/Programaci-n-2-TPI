#ifndef SISMOV_H
#define SISMOV_H

#include "grilla.h"
#include "personaje.h"
  /*
   * El objetivo de esta clase es calcular en una matriz de booleanos todas las
   * casillas que son validas para moverse por una unidad en las coordenadas "x" e "y"
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
      std::vector<personaje>& enemigos;
      bool *valido;
      int camino[16];
      void resetValido();
      void resetCamino();
      void movRango(int x, int y, int mov);
      bool buscarCaminoPriv(int x, int y, int mov, int profundidad);
      void achicarCamino();
      int calcDistCamino(int low, int high);
      bool hayNumeroDistinto(int low, int high);
      bool esDir(int num);
    public:
      SisMov(int x, int y, Grilla *g, std::vector<personaje>& e);
      void setEnemigos(std::vector<personaje>& e);
      void setDestino(int x, int y);
      bool Alcanzable(int x, int y);
      void calcularCamino();
      void buscarCamino(int x, int y, int mov);
      void calcularMovimiento(int x, int y, int mov);
      void resizeGrid(Grilla *g);
      const int* getCamino();
      const bool *getValido();
      ~SisMov();
  };

#endif
