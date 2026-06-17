#include"adminclase.h"

AdminClase::AdminClase()
{
  nClases = 3;
  clase = nullptr;
  clase = new claseTrabajo*[3]{};
  if(clase == nullptr)
  {
    nClases = 0;
    return;
  }
  //como dije está hardcodeado pero se tendria que poder poner con un setter
  clase[0] = new Guerrero;
  clase[1] = new Arquero;
  clase[2] = new Medico;

}
claseTrabajo *AdminClase::getClase(int idClase)
{
  if(idClase >= 0 && idClase < nClases)
    return clase[idClase];
  else
    return nullptr;
}
AdminClase::~AdminClase()
{
  if(clase != nullptr)
  {
    for(int i = 0; i < 3; i++)
      if(clase[i] != nullptr)
        delete clase[i];
    delete [] clase;
  }
}
