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

enum DIRECCIONES
{
  NULO,
  ARRIBA,
  IZQUIERDA,
  ABAJO,
  DERECHA,
  ENTER,
  RETROCESO
};

//Recomendaría que los enums sean en MAYUSCULAS, por consistencia
enum ESTADO_JUEGO
{
    CURSOR_LIBRE,
    PERSONAJE_SELECCIONADO,
    MENU_PRINCIPAL,
    MENU_INGAME,
    ANIMACION_BLOQUEANTE
};

enum ACCION_PERSONAJE
{
  SIN_ACCION,
  ACTIVO
};

enum class TIPO_PERSONAJE {
    JUGADOR,
    NO_JUGADOR
};

const int profundidadMax = 16;

#endif
