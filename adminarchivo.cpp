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
  int leyoAlgo = fread(&leido, 1, 1, arch);
  for(int i = 0; leido != '\n' && leido != '\r' && leyoAlgo; i++)
  {
    str[i] = leido;
    fread(&leido, 1, 1, arch);
  }
  while(leido != '\n' && leyoAlgo)
    fread(&leido, 1, 1, arch);
}

int AdminArchivo::avanzarHastaChar(char start)
{
  int nColumnas = 0;
  int avanzo;
  if(arch == nullptr)
    return 0;
  char leido = 0;
  avanzo = fread(&leido, 1, 1, arch);
  if(avanzo)
    nColumnas++;
  while(leido != start && avanzo)
  {
    avanzo = fread(&leido, 1, 1, arch);
    nColumnas++;
  }
  return nColumnas;
}

int AdminArchivo::contarLineas()
{
  int nFilas = 0;
  int nChar;
  char *txt = nullptr;
  if(arch == nullptr)
    return nFilas;
  fseek(arch, 0, SEEK_END);
  nChar = ftell(arch);
  txt = new char[nChar];
  fseek(arch, 0, SEEK_SET);
  fread(txt, 1, nChar, arch);
  for(int i = 0; i < nChar; i++)
    if(txt[i] == '\n')
      nFilas++;
  return nFilas + 1;
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
