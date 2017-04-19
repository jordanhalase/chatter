/*
 * Owen Monsma
 * ChatEdge.cpp
 * 19 April 2017
 */

#include "ChatEdge.hpp"

namespace Chatter{
  ChatEdge::ChatEdge() {
    next = new ChatNode();
    seen = false;
    exitline = false;
  }
  ChatEdge::~ChatEdge() {
    printf("ChatEdge destructor\n");
    delete next;
  }

  void ChatEdge::setNext(ChatNode* n) {
    next = n;
  }

  ChatNode* ChatEdge::getNext() {
    return next;
  }

  void ChatEdge::setLine(std::string l){
    line = l;
  }

  std::string ChatEdge::getLine() {
    seen = true;
    return line;
  }

  void ChatEdge::setExit(bool e){
    exitline = e;
  }

  bool ChatEdge::getExit(){
    return exitline;
  }

}
