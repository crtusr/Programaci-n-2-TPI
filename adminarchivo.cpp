#include"adminarchivo.h"
#include <cstdlib>

AdminArchivo::AdminArchivo(const char *nombre)
{
  arch = nullptr;
  nomArch = nombre;
}
int AdminArchivo::abrir()
{
  if(arch == nullptr)
  {
    arch = fopen(nomArch, "rb+");
    if(arch == nullptr)
    {
      return 1;
    }
  }
  else
    return 0x7fffffff; //simplemente un numero raro que no parezca aleatorio
  return 0;
}
int AdminArchivo::cerrar()
{
  return fclose(arch);
}
void AdminArchivo::leerLinea(char *str)
{
  if(arch == nullptr)
    return;
  char leido = 0;
  fread(&leido, 1, 1, arch);
  for(int i = 0; leido != '\n' && leido != '\r'; i++)
  {
    str[i] = leido;
    fread(&leido, 1, 1, arch);
  }
  while(leido != '\n')
    fread(&leido, 1, 1, arch);
}
int AdminArchivo::leerNumero()
{
  char str[20];
  leerLinea(str);
  return atoi(str);
}
int AdminArchivo::leerInt()
{
  int numero;
  fread(&numero, sizeof(int), 1, arch);
  return numero;
}
//dificil habria que una vez leido el personaje se setee grilla, y textura
/*
personaje AdminArchivo::leerPersonaje()
{
  personaje pers;
  fread(&pers, sizeof(pers), 1, arch);
  return pers;
}
*/
void AdminArchivo::escribirInt(int num)
{
  fwrite(&num, sizeof(int), 1, arch);
  return;
}

//lo más sensato sería solo escribir los datos relevantes del personaje
void AdminArchivo::escribirPersonaje(personaje &pers)
{
  fwrite(&pers, sizeof(personaje), 1, arch);
  return;
}
