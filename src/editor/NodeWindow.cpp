#include "NodeWindow.hpp"

NodeWindow::NodeWindow(Chatter* ch, int y){
  this->chat = ch;
  el_node = newwin(9, COLS - 2, y, 1);
  wbkgd(el_node, COLOR_PAIR(1));
}

NodeWindow::~NodeWindow(){
  delwin(el_node);
}

void NodeWindow::update(){
  wmove(el_node, 1,1);
  wprintw(el_node, "Test node text\n1.\n2.\n3.\n4.\n5.\n6.");
  wrefresh(el_node);
}
