#include <cstdio>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "grilla.h"
#include "defaultcelda.h"
#include "celdaterrestre.h"

enum baldosas
{
  DEFAULT,
  PRADO,
  BOSQUE,
  MONTANIA,
  MAR
};

const int TamanioDeLaBaldosa = 64;

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
  const int tamFila = grilla.getMaxX();
  int i = 0;
  char tipoCelda; 
  int error = 0;
  FILE *archMapa = nullptr;
  archMapa = fopen(nomArch, "rb");
  if(archMapa == nullptr)
  {
    error = -1;
    return error;
  }
  while(fread(&tipoCelda, 1, 1, archMapa) && (i < (grilla.getMaxX() * grilla.getMaxY())))
  {
    //printf("celda: %x %ld\n", tipoCelda, ftell(archMapa));
    switch(tipoCelda)
    {
      case '\n':
      case '\r':
        break;
      case '0':
        grilla.setCelda(new DefaultCelda(i % tamFila, i / tamFila, 255, tex[DEFAULT]));
        i++;
        break;
      case 'P':
        grilla.setCelda(new CeldaTerrestre(i % tamFila, i / tamFila, 1, tex[PRADO]));
        i++;
        break;
      case 'B':
        grilla.setCelda(new CeldaTerrestre(i % tamFila, i / tamFila, 2, tex[BOSQUE]));
        i++;
        break;
      case 'M':
        grilla.setCelda(new CeldaTerrestre(i % tamFila, i / tamFila, 4, tex[MONTANIA]));
        i++;
        break;
      default:
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

int cargarTexturasDeCeldas(sf::Texture *tex, int nTexturas)
{
  const char *nomArchivo[10] = 
  {
    "Tiles/defaulttile.bmp",
    "Tiles/prado.bmp",
    "Tiles/bosque.bmp",
    "Tiles/montaña.bmp",
    "Tiles/mar.bmp"
  };
  int todoBien;
  for(int i = 0; i < nTexturas; i++)
    {
      todoBien = tex[i].loadFromFile(nomArchivo[i]);
      if(!todoBien)
        return -1;
    }
  return 0;
}

int main()
{
  int err;
  //Esto declara la pantalla
  sf::RenderWindow window(sf::VideoMode({1024, 768}), "SFML 3");
  sf::Texture texCelda[10];
  sf::Texture texClase[5];
  err = cargarTexturasDeCeldas(texCelda, 5);
  if(err)
    return -1;
  Grilla tablero(TamanioDeLaBaldosa, 4, 4);
  cargarMapa(tablero, "testmap.txt",texCelda);
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
    tablero.render(window);
    window.display();
  }

  return 0;
}
