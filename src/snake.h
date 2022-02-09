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
  bool death = false;
  int direction = KEY_RIGHT;
  int level = 0;
  int speed = 40;
  int ticks = 0;
  CPoint food;
  vector <CPoint> snake_parts;

  void reset(){
    pause_game = false;
    death = false;
    direction = KEY_RIGHT;
    level = 0;
    speed = 50;
    ticks = 0;
    int head_x = rand() % (geom.size.x - 4) + 4;
    int head_y = rand() % (geom.size.y - 4) + 4;
    snake_parts.clear();
    snake_parts.push_back(CPoint(head_x, head_y));
    snake_parts.push_back(CPoint(head_x-1, head_y));
    snake_parts.push_back(CPoint(head_x-2, head_y));
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

    if(snake_parts[0].x == 0) snake_parts[0].x = geom.size.x - 2;
    if(snake_parts[0].x == geom.size.x - 1) snake_parts[0].x = 1;
    if(snake_parts[0].y == 0) snake_parts[0].y = geom.size.y - 2;
    if(snake_parts[0].y == geom.size.y - 1) snake_parts[0].y = 1;

    for(unsigned int i = 1; i < snake_parts.size(); i++){
      if(snake_parts[0].x == snake_parts[i].x && snake_parts[0].y == snake_parts[i].y)
        return false;
    }

    if(snake_parts[0] == food){
      snake_parts.push_back(tail_part);
      generateFood();
      if(speed > 1) speed--;
      level++;
    }
    return true;
  }

  void draw_game(){
    if(move() == false){
      pause_game = true;
      death = true;
    }
    gotoyx(snake_parts[0].y + geom.topleft.y ,snake_parts[0].x + geom.topleft.x);
    printc('*');

    for(unsigned int i = 1; i < snake_parts.size(); i++){
      gotoyx(snake_parts[i].y + geom.topleft.y ,snake_parts[i].x + geom.topleft.x);
    printc('+');
    }

    gotoyx(food.y + geom.topleft.y ,food.x + geom.topleft.x);
    printc('O');

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
  CSnake(CRect r, char _c = ' ') : CFramedWindow(r, _c) {
    srand(time(NULL));
    reset();
    pause_game = true;
    draw_game();
  }

  bool handleEvent(int key){
    if(!pause && key == ERR){
      ticks++;
      if(speed <= ticks) {
        return move();
        ticks = 0;
      }
    }
    if(!died && key == 'p'){
      pause = !pause;
      return true;
    }
    if(key == 'q') exit(0);
    if(key == 'r'){
      reset();
      return true;
    }

    if(key == '\t') return true;

    if(!died && !pause){
      if( (key == KEY_UP && direction != KEY_DOWN) || 
      (key == KEY_RIGHT && direction != KEY_LEFT) ||
      (key == KEY_DOWN && direction != KEY_UP) ||
      (key == KEY_LEFT && direction != KEY_RIGHT))
        direction = key;
      return true;
    }
    return CFramedWindow::handleEvent(key);
  }

  void paint(){
    CFramedWindow::paint();
    draw_game();
    if(!death){
      gotoyx(geom.topleft.y-1, geom.topleft.x);
      printl("| Level: %d || Speed: %d |", level, speed);
      if(pause) draw_pause();
    } else{
      draw_dead();
    }
  }
};

#endif
