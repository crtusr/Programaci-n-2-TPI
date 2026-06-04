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
  void moverpersonaje(personaje& pers, const int *dir);
  void mostrarpersonaje(personaje& pers,sf::RenderWindow& window);
  void Asignarpersonajes(personaje& pers);
  void secuencia(personaje& pers);
  void cambiarpersonaje(personaje& pers);

};
#endif // MANAGERPERSONAJE_H_INCLUDED
