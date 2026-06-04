#ifndef MANAGERPERSONAJE_H_INCLUDED
#define MANAGERPERSONAJE_H_INCLUDED
#include <SFML/Graphics.hpp>
#include "personaje.h"



class managerpersonaje {
private:
  int cont=0;
  int actual=0;
public:

  int getactual();
  void moverpersonaje(personaje& pers);
  void mostrarpersonaje(personaje& pers,sf::RenderWindow& window);
  void Asignarpersonajes(personaje& pers);
  void secuencia(personaje& pers);
  void cambiarpersonaje(personaje& pers);

};
#endif // MANAGERPERSONAJE_H_INCLUDED
