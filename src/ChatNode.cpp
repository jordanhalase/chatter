#include "ChatNode.hpp"
#include <stdio.h>

namespace Chatter{
  ChatNode::ChatNode() :
    maxResp(6)
    {
      numResp = 0;
      responses = new ChatEdge*[maxResp];
      line = "placeholder";
    }

  ChatNode::~ChatNode(){
    printf("ChatNode destructor\n");
    for (int i = 0; i < maxResp; ++i){
      delete responses[i];
      responses[i] = NULL;
    }
    delete[] responses;
  }

  void ChatNode::setLine(std::string l){
    line = l;
  }

  void ChatNode::addResp(ChatEdge* r){
    if (numResp < maxResp){
      responses[numResp++] = r;
    }
  }

  ChatEdge* ChatNode::respond(int option){
    return responses[option];
  }
}
