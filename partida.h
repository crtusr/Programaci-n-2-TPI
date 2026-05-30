#ifndef PARTIDA_H
#define PARTIDA_H


class Partida
  {
    private:
      int ronda;
      int turno;
    public:
      Partida(int r = 0, int t = 0);
      int getRonda();
      int getTurno();
      void pasarTurno();
  };

#endif
