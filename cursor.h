#ifndef CURSOR_H
#define CURSOR_H

  class Cursor
  {
    private:
      int xPos;
      int yPos;
    public:
      Cursor(int x, int y);
      int getXPos();
      int getYPos();
      void setPos(int x, int y);
      void mover(int dir);
  };

#endif
