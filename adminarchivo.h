#ifndef ADMINARCHIVO_H
#define ADMINARCHIVO_H
#include <cstdio>
#include "personaje.h"

  class AdminArchivo
  {
    private:
      FILE *arch;
      const char *nomArch;
    public:
      AdminArchivo(const char *nombre);
      int abrir();
      int cerrar();
      void leerLinea(char *str);
      int avanzarHastaChar(char start);
      int contarLineas();
      int leerNumero();
      int leerInt();
      personaje leerPersonaje();
//      void escribirLinea(char *str);
      void escribirInt(int num);
      void escribirPersonaje(personaje &pers);
  };

#endif
