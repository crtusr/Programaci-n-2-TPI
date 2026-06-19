#include "utilidades.h"
#include "constantes.h"

std::string tipoToString(TIPO_PERSONAJE t)
{
    switch (t)
    {
        case TIPO_PERSONAJE::JUGADOR: return "JUGADOR";
        case TIPO_PERSONAJE::NO_JUGADOR: return "NO_JUGADOR";
        default: return "DESCONOCIDO";
    }
}

std::string ClaseToString(CLASE_PERSONAJE c)
{
    switch (c)
    {
        case CLASE_PERSONAJE::CLASE_GUERRERO: return "GUERRERO";
        case CLASE_PERSONAJE::CLASE_ARQUERO: return "ARQUERO";
        case CLASE_PERSONAJE::CLASE_MEDICO: return "MEDICO";
        default: return "DESCONOCIDO";
    }
}