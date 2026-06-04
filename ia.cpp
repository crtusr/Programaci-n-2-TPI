#include "ia.h"

IA::IA(personaje *p, Grilla *g) : personajeIA(p) {


}

personaje* IA::getPersonajeIA() {
    return personajeIA;
}

void IA::setPersonajeIA(personaje *p) {
    personajeIA = p;
}

personaje* IA::buscarEnemigoMasCercano() {
    // Implementar lógica para buscar el enemigo más cercano
    return nullptr; // Placeholder para compilar
}

personaje* IA::buscarAliadoMasCercano() {
    // Implementar lógica para buscar el aliado más cercano
    return nullptr; // Placeholder para compilar
}

void IA::moverEnemigo() {
    // Implementar lógica para mover al enemigo
}

void IA::moverAliado() {
    // Implementar lógica para mover al aliado
}

void IA::atacarEnemigo() {
    // Implementar lógica para atacar al enemigo
}
