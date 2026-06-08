#include "ia.h"

IA::IA(personaje *p, Grilla *g) : personajeIA(p) {
    vectorPNJ.reserve(20); // Reservar espacio para 20 personajes no jugadores (PNJ)
    vectorPJ.reserve(20);  // Reservar espacio para 20 personajes jugadores (PJ)
}

personaje* IA::getPersonajeIA(personaje *p) {
    return personajeIA;
}

void IA::setPersonajeIA(personaje *p) {
    personajeIA = p;
}

void IA::agregrarPNJ(personaje *p) {
    if (vectorPNJ.size() < 20) {
        vectorPNJ.push_back(p);
    } else {
        // Manejar el caso en que se alcance la capacidad máxima del vector
        std::cerr << "No se pueden agregar más personajes no jugadores (PNJ)\n";
    }
}

void IA::agregarPJ(personaje *p) {
    if (vectorPJ.size() < 20) {
        vectorPJ.push_back(p);
    } else {
        // Manejar el caso en que se alcance la capacidad máxima del vector
        std::cerr << "No se pueden agregar más personajes jugadores (PJ)\n";
    }
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
