#ifndef MANAGERPERSONAJE_H_INCLUDED
#define MANAGERPERSONAJE_H_INCLUDED
#include <SFML/Graphics.hpp>
#include "personaje.h"



class managerpersonaje {
private:
  int cont;
  int actual;
  int caminoIndice;
public:

  managerpersonaje();
  void resetCaminoIndice();
  int getactual();
  int moverpersonaje(personaje& pers, const int *dir);
  void moverpersonaje(personaje& pers);
  void mostrarpersonaje(vector<personaje>& pers,RenderWindow& window);
  void Asignarpersonajes(personaje& pers);
  void secuencia(personaje& pers);
  void cambiarpersonaje(personaje& pers);
  void cambiardireccion(vector<personaje>& pers, int dir);
  int comprobarlugar(int x,int y,vector<personaje> pers);
  void actualizarpersonaje(vector<personaje>& pers);
  int contarPersonajesActivos(vector<personaje>& pers);

};
#endif // MANAGERPERSONAJE_H_INCLUDED
