#include <ncurses.h>
#include <stdio.h>
#include "Timeline.hpp"
#include "NodeWindow.hpp"
#include "Chatter.hpp"

#define CNODE_H 1
#define NNODE_H 11

#define MSGS_H 20
#define PROMPT_H 21

#define KEY_ESC 27

enum Mode{
  VIEW,
  EDIT,
  PLAY
};

void init();

void update();
void handleInput(int ch);
void changeMode(Mode m);
void printSystemMsg(const char* msg);
void cleanup();

void setNNode();


// Our global variables
bool running = true;
bool unsaved = false;
Chatter chat = Chatter();
int cShowingFrame = 0;
int nShowingFrame = 0;

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
  // testing with a previously created chat
  chat.loadChat("../save/save1");

  initscr();
  noecho();
  raw();
  nonl();
  curs_set(0);
  start_color();
  init_pair(1, COLOR_BLACK, COLOR_CYAN);
  init_pair(2, COLOR_CYAN, COLOR_BLACK);
  init_pair(3, COLOR_BLACK, COLOR_WHITE);
  wbkgd(stdscr, COLOR_PAIR(1));

  changeMode(VIEW);
  mvaddch(MSGS_H, 1, '>');
  mvaddch(PROMPT_H, 1, ':');

  keypad(stdscr, TRUE);
  refresh();

  tl = new Timeline(&chat);
  tl->goToFrame(cShowingFrame);
  cnode = new NodeWindow(&chat, CNODE_H);
  nnode = new NodeWindow(&chat, NNODE_H);


  cnode->update();
  nnode->update();
  tl->update();
  printSystemMsg("Editor initialized!");
}

void handleInput(int ch){
  // Global key commands
  switch(ch){
    case 'q':
      if (unsaved){
        printSystemMsg("Unsaved changes! Save your changes, or use Q to discard changes and quit.");
      } else {
        running = false;
      }
      break;
    case 'Q':
      running = false;
      break;
    default:
      //printSystemMsg("key not supported.");
      break;
  }
  // Mode-sensitive key commands
  switch(mode){
    case VIEW:
      switch(ch){
        case '[':
          cShowingFrame = tl->frameLeft();
          /*
          cnode->setNode(cShowingFrame);
          nShowingFrame = cnode->getSelNextLine();
          nnode->setNode(nShowingFrame);
          tl->setNextFramePos(nShowingFrame);
          */
          break;
        case ']':
          cShowingFrame = tl->frameRight();
          /*
          cnode->setNode(cShowingFrame);
          nShowingFrame = cnode->getSelNextLine();
          nnode->setNode(nShowingFrame);
          tl->setNextFramePos(nShowingFrame);
          */
          break;
        case KEY_UP:
          nShowingFrame = cnode->chLineUp();
          /*
          nnode->setNode(nShowingFrame);
          tl->setNextFramePos(nShowingFrame);
          */
          break;
        case KEY_DOWN:
          nShowingFrame = cnode->chLineDn();
          /*
          nnode->setNode(nShowingFrame);
          tl->setNextFramePos(nShowingFrame);
          */
          break;
        case '\r':
        case '\n':
        case KEY_ENTER:
          unsaved = true;
          changeMode(EDIT);
          break;
        default:
          break;
      }
      update();
      break;

    case EDIT:
      switch(ch){
        case KEY_ESC:
          changeMode(VIEW);
          break;
        default:
          break;
      }
      update();
      break;

    case PLAY:
      break;
  }
}

void update(){
  cnode->setNode(cShowingFrame);
  nShowingFrame = cnode->getSelNextLine();
  nnode->setNode(nShowingFrame);
  tl->setNextFramePos(nShowingFrame);
}

void changeMode(Mode m){
  mode = m;
  move(0,COLS - 5);
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
  refresh();
}

void printSystemMsg(const char* msg){
  move(MSGS_H, 2);
  clrtoeol();
  printw(msg);
  refresh();
}

void cleanup(){
  delete tl;
  delete cnode;
  delete nnode;
  endwin();
}
