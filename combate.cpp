#include "combate.h"
#include "ctime"

Combate::Combate(Grilla *g, personaje *at, personaje *def)
{
  atacante = at;
  defendiente = def;
  celdaAtac = (CeldaTerrestre *)g->getCelda(atacante->getPosx(), atacante->getPosy());
  celdaDef = (CeldaTerrestre *)g->getCelda(defendiente->getPosx(), defendiente->getPosy());
}

void Combate::pelea()
{
  srand(time(NULL));
  int danioAtac;
  /*
    int danioDef;
    float porcBloqAtac;
  */
  float porcBloqDef;
  
  danioAtac = atacante->getFuerza() - defendiente->getDefensa() - celdaDef->getDefensa();
  /*
    danioDef = defendiente->getFuerza() - atacante->getDefensa() - celdaAtac->getDefensa();

    porcBloqAtac = atacante->getDefensa() * 5 + celdaAtac->getDefensa() * 10;
  */
  porcBloqDef = defendiente->getDefensa() * 5 + celdaDef->getDefensa() * 10;

  if(rand() % 100 >= porcBloqDef)
  {
    if(defendiente->restarHp(danioAtac))
      return;
  }
  /*
  if(rand() % 100 >= porcBloqAtac)
  {
    if(atacante->restarHp(danioDef))
      return;
  }
  */
  return ;
}
