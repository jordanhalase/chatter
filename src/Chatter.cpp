/*
 * Owen Monsma
 * Chatter.cpp
 * 19 April 2017
 */
#include <iostream>
#include "Chatter.hpp"

namespace Chatter{
  Chatter::Chatter(){
    entry = new ChatNode();
    current = entry;
    chatting = false;
  }

  Chatter::~Chatter(){
    printf("Chatter destructor\n");
    delete entry;
    current = NULL;
  }

  void Chatter::loadChat(std::string file, filemode mode){

  }

  void Chatter::setEntry(ChatNode* e){
    entry = e;
    current = entry;
  }

  void Chatter::chat(){
    chatting = true;
    while (chatting){
      std::cout << current->getLine() << std::endl;
      printf("number of responses: %d\n", current->getNumResp());
      if (current->getNumResp() > 0){
        for (int i = 0; i < current->getNumResp(); ++i){
          std::cout << current->respond(i)->getLine() << std::endl;
        }
      }

      chatting = false;
    }
  }

  void Chatter::initTestChat(){
    entry->setLine("Hello, this is a chatter.");


    ChatEdge* resp1
    resp1->setLine("This is the first response.");
    resp1->setNext(new ChatNode());

    ChatEdge* resp2 = new ChatEdge();
    resp2->setLine("Aaaand the second response.");
    resp2->setNext(new ChatNode());

    entry->addResp(resp1);
    entry->addResp(resp2);

  }
}
