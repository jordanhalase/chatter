#include <ncurses.h>
#include <stdio.h>
#include "Timeline.hpp"
#include "NodeWindow.hpp"
#include "Chatter.hpp"

#define CNODE_H 1
#define NNODE_H 11

#define PROMPT_H 21

enum Mode{
  VIEW,
  EDIT,
  PLAY
};

void init();

void update();
void handleInput(int ch);
void changeMode(Mode m);
void cleanup();


// Our global variables
bool running = true;
Chatter chat = Chatter();
int showingFrame = 0;

// UI components
Timeline* tl;
NodeWindow* cnode;
NodeWindow* nnode;

Mode mode;

int main(int argc, char* argv[]){
  init();
  while (running){
    int ch = getch();
    handleInput(ch);
  }

  cleanup();
  return 0;
}

void init(){

  initscr();
  noecho();
  curs_set(0);
  start_color();
  init_pair(1, COLOR_BLACK, COLOR_CYAN);
  init_pair(2, COLOR_CYAN, COLOR_BLACK);
  init_pair(3, COLOR_BLACK, COLOR_WHITE);
  wbkgd(stdscr, COLOR_PAIR(1));

  changeMode(VIEW);
  mvaddch(PROMPT_H, 1, ':');

  refresh();

  tl = new Timeline(&chat);
  tl->goToFrame(showingFrame);
  cnode = new NodeWindow(&chat, CNODE_H);
  nnode = new NodeWindow(&chat, NNODE_H);


  cnode->update();
  nnode->update();
  tl->update();
}

void handleInput(int ch){
  switch(mode){
    case VIEW:
      switch(ch){
        case '[':
          showingFrame = tl->frameLeft();
          break;
        case ']':
          showingFrame = tl->frameRight();
          break;
        default:
          running = false;
          break;
      }
      break;

    case EDIT:
      break;

    case PLAY:
      break;
  }
}

void changeMode(Mode m){
  mode = m;
  move(0,1);
  attron(A_BOLD);
  switch(m){
    case VIEW:
      printw("VIEW");
      break;
    case EDIT:
      printw("EDIT");
      break;
    case PLAY:
      printw("PLAY");
      break;
  }
  attroff(A_BOLD);
}

void cleanup(){
  delete tl;
  delete cnode;
  delete nnode;
  endwin();
}
