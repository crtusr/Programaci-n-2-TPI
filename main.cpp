#include <cstdio>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "grilla.h"
#include "defaultcelda.h"

/*
class AdminTextura
{
  private:
    sf::texture tex[10]; //por ahora no más de 10 terrenos
    char tipoCelda[10];
  public:
    Admin
    
};
*/

int cargarMapa(Grilla &grilla, const char* nomArch, sf::Texture *tex)
{
  int i = 0;
  char tipoCelda[5]; 
  int error = 0;
  FILE *archMapa = nullptr;
  archMapa = fopen(nomArch, "rb");
  if(archMapa == nullptr)
  {
    error = -1;
    return error;
  }
  while(i < (grilla.getMaxX() * grilla.getMaxY()))
  {
    fread(tipoCelda, 1, 1, archMapa);
    printf("celda: %x %ld\n", tipoCelda[0], ftell(archMapa));
    if(tipoCelda[0] == '0')
    {
      grilla.setCelda(i % grilla.getMaxX(), i / grilla.getMaxX(), new DefaultCelda(i % grilla.getMaxX(), i / grilla.getMaxX(), 255, tex[0]));
      i++;
    }
  }
  error = fclose(archMapa);
  if(error)
  {
    return error;
  }
  
  return 0;
}

int main()
{
  int err;
  //Esto declara la pantalla
  sf::RenderWindow window(sf::VideoMode({1024, 768}), "SFML 3");
  sf::Texture texCelda[10];
  err = texCelda[0].loadFromFile("Tiles/defaulttile.bmp");
  if(!err)
    return -1;
  Grilla tablero(32, 4, 4);
  cargarMapa(tablero, "testmap.txt",texCelda);
  //Acá se declaran objetos que se pueden dibujar con window.draw(objeto);
//  const sf::Font font("C:/WINDOWS/FONTS/CAMBRIA.TTC");
  //sf::Text text(font, "Gato", 50);  
  //const sf::Texture texture("sprite.bmp");
  //sf::Sprite sprite(texCelda[0]);
  //sf::Vector2<float> s2Pos(100,200);
  while (window.isOpen())
  {
    while (const std::optional<sf::Event> event = window.pollEvent())
    {
      //Acá se manejan los eventos
      if (event->is<sf::Event::Closed>())
      {
          window.close();
      }
      else if (event->is<sf::Event::KeyPressed>())
      {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
          
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
         
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        {
        
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        {
       
        }
      }
    }
    //Acá le mandas los comandos a la ventana para que dibuje objetos
    window.clear(sf::Color::Blue); 
    //window.draw(sprite);
    tablero.render(window);
    window.display();
  }

  return 0;
}
