#include "texmanager.h"
#include <cstdio>
#include <cstring>
#include "adminarchivo.h"


TexManager::TexManager(const char *archivos)
{
  AdminArchivo archivo(archivos);
  int nTexCeldas, nTexPers;
  char dirArchivo[64] = {0};
  archivo.abrir();
  nTexCeldas = archivo.leerNumero();
  nTexPers = archivo.leerNumero();
  for(int i = 0; i < nTexCeldas; i++)
  {
    archivo.leerLinea(dirArchivo);
    if(!celda[i].loadFromFile(dirArchivo))
    {
      printf("Ocurrio un error\n");
    }
    memset(dirArchivo, 0, 64);
  }

  for(int i = 0; i < nTexPers; i++)
  {
    archivo.leerLinea(dirArchivo);
    if(!personaje[i].loadFromFile(dirArchivo))
    {
      printf("Ocurrio un error\n");
    }
    memset(dirArchivo, 0, 64);
  }
  archivo.cerrar();
}
sf::Texture *TexManager::getPersonaje(int num)
{
  if(num < 10)
    return &personaje[num];
  else
    return nullptr;
}
sf::Texture *TexManager::getCelda(int num)
{
  if(num < 10)
    return &celda[num];
  else
    return nullptr;
}
