#ifndef __SNAKE_H__
#define __SNAKE_H__

#include <cstdlib>

#include "winsys.h"
#include "cpoint.h"
#include "screen.h"

class CSnake : public CFramedWindow
{
private:
  int direction = KEY_RIGHT;
  int level = 0;
  int speed = 40;
  int ticks = 0;
  CPoint food;
  vector <CPoint> snake_parts;

  void reset(){
    direction = KEY_RIGHT;
    level = 0;
    int head_x = rand() % (geom.size.x - 4) + 4;
    int head_y = rand() % (geom.size.y - 4) + 4;
    parts.clear();
    parts.push_back(CPoint(head_x, head_y));
    parts.push_back(CPoint(head_x-1, head_y));
    parts.push_back(CPoint(head_x-2, head_y));
    paint();
  }
public:
  CSnake(CRect r, char _c = ' ');
};

#endif
