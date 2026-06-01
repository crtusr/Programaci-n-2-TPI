#include "proc_input.h"
#include "constantes.h"

int ProcInput::tecla(sf::Keyboard::Key tecla)
{
  switch(tecla)
  {
    case sf::Keyboard::Key::Up: 
      return ARRIBA;
    case sf::Keyboard::Key::Down:
      return ABAJO;
    case sf::Keyboard::Key::Left:
      return IZQUIERDA;
    case sf::Keyboard::Key::Right:
      return DERECHA;
    case sf::Keyboard::Key::Enter:
      return ENTER;
    case sf::Keyboard::Key::Backspace:
      return RETROCESO;
    default:
      return NULO;


  }   
}

