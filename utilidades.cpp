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