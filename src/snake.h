#ifndef __SNAKE_H__
#define __SNAKE_H__

#include <cstdlib>

#include "winsys.h"
#include "cpoint.h"
#include "screen.h"

class CSnake : public CFramedWindow
{
private:
  bool pause_game = false;
  bool help_menu = false;
  bool death = false;
  int direction = KEY_RIGHT;
  int level = 0;
  int speed = 40;
  int ticks = 0;
  CPoint food;
  vector <CPoint> snake_parts;

  void reset(){
    pause = false;
    help = false;
    death = false;
    direction = KEY_RIGHT;
    level = 0;
    speed = 40;
    ticks = 0;
    int head_x = rand() % (geom.size.x - 4) + 4;
    int head_y = rand() % (geom.size.y - 4) + 4;
    parts.clear();
    parts.push_back(CPoint(head_x, head_y));
    parts.push_back(CPoint(head_x-1, head_y));
    parts.push_back(CPoint(head_x-2, head_y));
    paint();
  }

  void generateFood(){
    CPoint spot;
    while(true){
      spot = CPoint( (rand() % (geom.size.x - 1)) + 1, (rand() % (geom.size.y -1 )) + 1);
      for(int i = 0; i < snake_parts.size(); i ++){
        if(spot == snake_parts[i]) continue;
      }
      break;
    }
    food = spot;
  }
public:
  CSnake(CRect r, char _c = ' ');
};

#endif
