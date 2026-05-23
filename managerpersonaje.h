#ifndef MANAGERPERSONAJE_H_INCLUDED
#define MANAGERPERSONAJE_H_INCLUDED
#include <SFML/Graphics.hpp>
#include "personaje.h"



class managerpersonaje {
private:


public:

void moverpersonaje(personaje& pers);
void mostrarpersonaje(personaje& pers,sf::RenderWindow& window);
void Asignarpersonajes(personaje& pers);


};
#endif // MANAGERPERSONAJE_H_INCLUDED
