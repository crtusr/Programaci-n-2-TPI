#ifndef CONSTANTES_H
#define CONSTANTES_H

enum CELDAS
{
  DEFAULT,
  PRADO,
  BOSQUE,
  MONTANIA,
  MAR
};

enum TECLAS
{
  NULO,
  ARRIBA,
  IZQUIERDA,
  ABAJO,
  DERECHA,
  ENTER,
  RETROCESO,
  SPACE,
  F
};

//Recomendaría que los enums sean en MAYUSCULAS, por consistencia
enum EstadoJuego
{
    CURSOR_LIBRE,
    PERSONAJE_SELECCIONADO,
    MENU_PRINCIPAL,
    MENU_INGAME,
    ANIMACION_BLOQUEANTE,
    PREPARAR_ATAQUE
};

enum ACCION_PERSONAJE
{
  SIN_ACCION,
  ACTIVO
};

const int profundidadMax = 16;

#endif
