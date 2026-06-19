#ifndef ADMINCLASE_H
#define ADMINCLASE_H
#include"clasetrabajo.h"
#include"Guerrero.h"
#include"Arquero.h"
#include"Medico.h"

//de momento voy a hardcodear las clases para ahorrar tiempo
class AdminClase
{
  private:
    claseTrabajo **clase;
    int nClases;
  public:
    AdminClase();
    claseTrabajo *getClase(int idClase);
    ~AdminClase();
};

#endif
