#include "NodeWindow.hpp"

NodeWindow::NodeWindow(Chatter* ch, int y){
  this->chat = ch;
  el_node = newwin(9, COLS - 2, y, 1);
  wbkgd(el_node, COLOR_PAIR(3));
  showing = chat->getNode(0);
}

NodeWindow::~NodeWindow(){
  delwin(el_node);
}

void NodeWindow::setNode(int n){
  showing = chat->getNode(n);
}

void NodeWindow::update(){
  wmove(el_node, 1,1);
  wprintw(el_node, "Test node text\n 1.\n 2.\n 3.\n 4.\n 5.\n 6.");
  wrefresh(el_node);
}
