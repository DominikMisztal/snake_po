#ifndef __SNAKE_H__
#define __SNAKE_H__

#include <vector>
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

  bool move(){
    if(pause_game) return true;
    CPoint tail_part = snake_parts.back();
    for(unsigned int i = snake_parts.size() - 1; i > 0; i--) snake_parts[i] = snake_parts[i-1];

    if(direction == KEY_UP)         snake_parts[0] += CPoint(-1,0);
    else if(direction == KEY_RIGHT) snake_parts[0] += CPoint(0,1);
    else if(direction == KEY_DOWN)  snake_parts[0] += CPoint(1,0);
    else if(direction == KEY_LEFT)  snake_parts[0] += CPoint(0,-1);

    if(snake_parts[0].x == 0) parts[0].x = geom.size.x - 2;
    if(snake_parts[0].x == geom.size.x - 1) parts[0].x = 1;
    if(snake_parts[0].y == 0) parts[0].y = geom.size.y - 2;
    if(snake_parts[0].y == geom.size.y - 1) parts[0].y = 1;

    for(unsigned int i = 1; i < snake_parts.size(); i++){
      if(snake_parts[0].x == snake_parts[i].x && snake_parts[0].y == snake_parts[i].y)
        return false;
    }

    if(snake_parts[0] == food){
      snake_parts.push_back(tail);
      generateFood();
      level++;
    }
    return true;
  }

  void draw_game(){
    if(move() == false){
      pause = true;
      death = true;
    }
    gotoyx(snake_parts[0].y + geom.topleft.y ,snake_parts[0].x + geom.topleft.x);
    printc("*");

    for(unsigned int i = 1; i < snake_parts.size(); i++){
      gotoyx(snake_parts[i].y + geom.topleft.y ,snake_parts[i].x + geom.topleft.x);
    printc("+");
    }

    gotoyx(food.y + geom.topleft.y ,food.x + geom.topleft.x);
    printc("O");

  }

  void draw_pause(){
    gotoyx(geom.topleft.y + 2, geom.topleft.x + 2);
    printl("GAME PAUSED");
    gotoyx(geom.topleft.y + 3, geom.topleft.x + 2);
    printl("p - toggle play/pause mode");
    gotoyx(geom.topleft.y + 4, geom.topleft.x + 2);
    printl("r - restart");
    gotoyx(geom.topleft.y + 5, geom.topleft.x + 2);
    printl("q - quit the game");
    gotoyx(geom.topleft.y + 6, geom.topleft.x + 2);
    printl("Arrow keys: move the snake");
    gotoyx(geom.topleft.y + 7, geom.topleft.x + 2);
    printl("Arrow keys in pause mode: move the window");
  }

  void draw_dead(){
    gotoyx(geom.topleft.y + 2, geom.topleft.x + 2);
    printl("GAME OVER");
    gotoyx(geom.topleft.y + 3, geom.topleft.x + 2);
    printl("Score: %d", level);
  }

public:
  CSnake(CRect r, char _c = ' ');
};

#endif
