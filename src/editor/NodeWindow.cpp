#include "NodeWindow.hpp"

#define MARGIN_L 2

NodeWindow::NodeWindow(Chatter* ch, const int y)
{
  this->chat = ch;
  el_node = newwin(9, COLS - 2, y, 1);
  wbkgd(el_node, COLOR_PAIR(3));
  showingID = 0;
  showing = chat->getNode(showingID);
  lineSel = 0;

  changeLine(0);

  const int respOffset = 2;
  for (int i = 0; i < MAX_RESPS; i++) {
    wmove(el_node, i + respOffset, MARGIN_L);
    wprintw(el_node, "%d.", i + 1);
  }
}

NodeWindow::~NodeWindow()
{
  delwin(el_node);
}

void NodeWindow::setNode(const int n)
{
  if (n > -1) {
    showingID = n;
    showing = chat->getNode(showingID);
  }
  update();
}

void NodeWindow::update()
{
  wmove(el_node, 1, MARGIN_L);
  wclrtoeol(el_node);

  if (showing != NULL) {
    wprintw(el_node, showing->line.c_str());

    const int respOffset = 2;
    for (int i = 0; i < MAX_RESPS; i++) {
      wmove(el_node, i + respOffset, 3 + MARGIN_L);
      wclrtoeol(el_node);
      wprintw(el_node, showing->next[i].line.c_str());
    }
  }

  wrefresh(el_node);
}

void NodeWindow::setLine(const char* str)
{
  if (lineSel == 0) {
    //showing->line = str;
    chat->addLineToNode(showingID, str);
  } else {
    if ((lineSel - 1) < showing->resps) {
      chat->replaceResp(showingID, lineSel - 1, str);
    } else {
      chat->addResp(showingID, str, 0);
    }
    //showing->next[lineSel - 1].line = str;
  }
  update();
}

const char* NodeWindow::getLine()
{
  return showing->line.c_str();
}

int NodeWindow::chLineUp()
{
  return changeLine(lineSel - 1);
}

int NodeWindow::chLineDn()
{
  return changeLine(lineSel + 1);
}

int NodeWindow::getSelNextLine()
{
  if (lineSel == 0) {
    return showing->nodeID;
  } else {
    return showing->next[lineSel - 1].next;
  }
}

int NodeWindow::changeLine(int newL)
{
  // clear old marker
  mvwaddch(el_node, lineSel + 1, 1, ' ');
  if (newL < 0) {
    newL = 6;
  }
  lineSel = newL % 7;

  // draw new marker
  wmove(el_node, lineSel + 1, 1);
  waddch(el_node, '>');
  wrefresh(el_node);

  return getSelNextLine();
}
