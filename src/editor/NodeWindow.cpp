#include "NodeWindow.hpp"

NodeWindow::NodeWindow(Chatter* ch, int y){
  this->chat = ch;
  el_node = newwin(9, COLS - 2, y, 1);
  wbkgd(el_node, COLOR_PAIR(3));
  showing = chat->getNode(0);

  const int respOffset = 2;
  for (int i = 0; i < MAX_RESPS; i++){
    wmove(el_node, i + respOffset, 1);
    wprintw(el_node, "%d.", i + 1);
  }
}

NodeWindow::~NodeWindow(){
  delwin(el_node);
}

void NodeWindow::setNode(int n){
  showing = chat->getNode(n);
  update();
}

void NodeWindow::update(){
  wmove(el_node, 1,1);
  wclrtoeol(el_node);
  wprintw(el_node, showing->line.c_str());
  wrefresh(el_node);
}
