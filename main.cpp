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

void drawAt(sf::RectangleShape &sq, float x, float y, sf::RenderWindow &win)
{
  sq.setPosition(sf::Vector2f(x * 64, y * 64));
  win.draw(sq);
}

void drawMovRango(sf::RectangleShape &sq, Grilla &grid, bool *visitadas, sf::RenderWindow &win)
{
  int x, y;
  for(y = 0; y < grid.getMaxY(); y++)
    for(x = 0; x < grid.getMaxX(); x++)
      if(visitadas[x + (y * grid.getMaxX())])
        drawAt(sq, x, y, win);
}

void movRango(int x, int y, int mov, Grilla &grid, bool *visitadas)
{
  /*
  if(x < 0 || x >= grid.getMaxX() || y < 0 || y >= grid.getMaxY())
    return;*/
  if(!visitadas[x + (y * grid.getMaxX())])
  {
    visitadas[x + (y * grid.getMaxX())] = true;
  }
  if(y + 1 < grid.getMaxY() && mov >= grid.getCelda(x, y + 1)->getCostoMov())
    movRango(x, y + 1, mov - grid.getCelda(x, y + 1)->getCostoMov(), grid, visitadas);
  if(x - 1 >= 0 && mov >= grid.getCelda(x - 1, y)->getCostoMov())
    movRango(x - 1 , y, mov - grid.getCelda(x - 1 , y)->getCostoMov(), grid, visitadas);
  if(y - 1 >= 0 && mov >= grid.getCelda(x, y - 1)->getCostoMov())
    movRango(x, y - 1, mov - grid.getCelda(x, y - 1)->getCostoMov(), grid, visitadas);
  if(x + 1 < grid.getMaxX() && mov >= grid.getCelda(x + 1, y)->getCostoMov())
    movRango(x + 1, y, mov - grid.getCelda(x + 1, y)->getCostoMov(), grid, visitadas);
}




int main()
{
  int err;
  //Esto declara la pantalla
  sf::RenderWindow window(sf::VideoMode({1024, 768}), "SFML 3", sf::Style::Resize);
  sf::Texture texCelda[10];
  sf::Texture texClase[5];

  sf::RectangleShape square(sf::Vector2f(64,64));
  square.setFillColor(sf::Color(127, 127, 255, 127));
  

  bool visitadas[8*8] = {};
  err = cargarTexturasDeCeldas(texCelda, 5);
  if(err)
    return -1;
  Grilla tablero(TamanioDeLaBaldosa, 8, 8);
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
      else if(const auto *resized = event->getIf<sf::Event::Resized>())
      {
        sf::FloatRect newSize(sf::Vector2f(0, 0), sf::Vector2f(resized->size.x, resized->size.y));
        window.setView(sf::View(newSize));
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
    for(int i = 0; i < 64; i++)
      visitadas[i] = false;
    movRango(3,3, 3, tablero, visitadas);
    drawMovRango(square, tablero, visitadas, window);
    window.display();
  }

  return 0;
}
