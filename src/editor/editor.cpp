#include <ncurses.h>
#include <stdio.h>
#include "Timeline.hpp"
#include "NodeWindow.hpp"
#include "Chatter.hpp"

void init();

void update();
void draw();
void cleanup();


// Our global variables
bool running = true;
Chatter chat = Chatter();

// UI components
Timeline* tl;
NodeWindow* cnode;

int main(int argc, char* argv[]){
  init();
  while (running){
    int ch = getch();
    switch(ch){
      case '[':
        tl->frameLeft();
        break;
      case ']':
        tl->frameRight();
        break;
      default:
        running = false;
        break;
    }
  }

  cleanup();
  return 0;
}

void init(){
  initscr();
  noecho();
  curs_set(0);
  start_color();
  init_pair(1, COLOR_BLACK, COLOR_WHITE);
  init_pair(2, COLOR_CYAN, COLOR_BLACK);

  tl = new Timeline(&chat);
  cnode = new NodeWindow(&chat, 1);
  wbkgd(stdscr, COLOR_PAIR(2));

  refresh();
  tl->update();
  cnode->update();
}

void cleanup(){
  delete tl;
  delete cnode;
  endwin();
}