#include "combate.h"
#include "ctime"

Combate::Combate(Grilla *g, personaje *at, personaje *def)
{
  atacante = at;
  defendiente = def;
  celdaAtac = g->getCelda(atacante->getPosx(), atacante->getPosy());
  celdaDef = g->getCelda(defendiente->getPosx(), defendiente->getPosy());
}

void Combate::pelea()
{
  srand(time(NULL));
  int danioAtac, danioDef;
  float porcBloqAtac, porcBloqDef;
  


  return;
}
