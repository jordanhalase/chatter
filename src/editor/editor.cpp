#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include "Timeline.hpp"
#include "NodeWindow.hpp"
#include "Chatter.hpp"

#define CNODE_H 1
#define NNODE_H 11

#define MSGS_H 20
#define PROMPT_H 21

#define KEY_ESC 27

enum Mode {
  VIEW,
  EDIT,
  PLAY
};

// Our global variables
bool running = true;
bool unsaved = false;
Chatter chat = Chatter();
int cShowingFrame = 0;
int nShowingFrame = 0;
Mode mode;

// UI components
Timeline* tl = nullptr;
NodeWindow* cnode = nullptr;
NodeWindow* nnode = nullptr;

void printSystemMsg(const char* msg)
{
  move(MSGS_H, 2);
  clrtoeol();
  printw(msg);
  refresh();
}

void changeMode(Mode m)
{
  mode = m;
  move(0, COLS - 5);
  attron(A_BOLD);
  switch(m) {
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

void init(std::string filename)
{
  // testing with a previously created chat
  try {
    chat.loadChat(filename);
  } catch (std::exception ex) {
    fprintf(stderr, "Could not load file %s\n", filename.c_str());
    abort();
  }

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

void update()
{
  cnode->setNode(cShowingFrame);
  nShowingFrame = cnode->getSelNextLine();
  nnode->setNode(nShowingFrame);
  tl->setNextFramePos(nShowingFrame);
}

void clearSystemMsg()
{
  move(MSGS_H, 2);
  clrtoeol();
}

void getInput(char* buf)
{
  move(PROMPT_H, 2);
  clrtoeol();
  echo();
  curs_set(1);
  getstr(buf);
  curs_set(0);
  noecho();
  move(PROMPT_H, 2);
  clrtoeol();
}

void saveChat()
{
  printSystemMsg("Enter filename to save:");
  char path[40] = "./";
  char name[32];
  getInput(name);
  strcat(path, name);
  printSystemMsg(path);
  try {
    chat.saveChat(path);
    clearSystemMsg();
    unsaved = false;
  } catch (std::exception ex) {
    printSystemMsg("Error on saving.");
  }
}

void loadChat()
{
  printSystemMsg("Enter filename to load:");
  char path[40] = "./";
  char name[32];
  getInput(name);
  strcat(path, name);
  try {
    chat.loadChat(path);
    printSystemMsg(path);
    unsaved = false;
  } catch (std::exception ex) {
    printSystemMsg("File not found.");
  }
}

void editLine()
{
  move(PROMPT_H, 2);
  clrtoeol();
  //printw(nnode->getLine());
  char buf[128];
  getInput(buf);
  cnode->setLine(buf);
}

void handleInput(int ch)
{
  // Global key commands
  switch(ch) {
    case 'q':
      if (unsaved) {
        printSystemMsg("Unsaved changes! Save your changes, or use Q to discard changes and quit.");
      } else {
        running = false;
      }
      break;
    case 'Q':
      running = false;
      break;
    case 's':
      saveChat();
      break;
    case 'l':
      loadChat();
      break;
    case KEY_LEFT:
      cShowingFrame = tl->frameLeft();
      break;
    case KEY_RIGHT:
      cShowingFrame = tl->frameRight();
      break;
    case KEY_UP:
      nShowingFrame = cnode->chLineUp();
      break;
    case KEY_DOWN:
      nShowingFrame = cnode->chLineDn();
      break;
    case 't':
      printSystemMsg("Enter a string:");
      char buf[128];
      getInput(buf);
      printSystemMsg(buf);
      break;
    case '\r':
    case '\n':
    case KEY_ENTER:
      unsaved = true;
      changeMode(EDIT);
      editLine();
      changeMode(VIEW);
      break;
    default:
      break;
  }
  update();
}

void cleanup()
{
  delete tl;
  delete cnode;
  delete nnode;
  endwin();
}

int main(int argc, char* argv[])
{
  std::string filename = "save";
  if (argc > 1) {
    filename = argv[1];
  }
  init(filename);
  while (running) {
    int ch = getch();
    handleInput(ch);
  }
  cleanup();
  return 0;
}

