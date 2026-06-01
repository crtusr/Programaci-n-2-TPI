#include "cursor.h"
#include "constantes.h"

CursorJuego::CursorJuego(int x, int y) {
    xPos = x;
    yPos = y;
}

int CursorJuego::getXPos() {
    return xPos;
}

int CursorJuego::getYPos() {
    return yPos;
}

void CursorJuego::setPos(int x, int y) {
    xPos = x;
    yPos = y;
}

void CursorJuego::mover(int dir) {
    switch(dir) {
        case ARRIBA:
            yPos--;
            break;
        case ABAJO:
            yPos++;
            break;
        case IZQUIERDA:
            xPos--;
            break;
        case DERECHA:
            xPos++;
            break;
    }
}
