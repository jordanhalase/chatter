/* Chatter.c
 * Owen Monsma
 * 25 April 2017
 */

#include "Chatter.hpp"

Chatter::Chatter(): chatSize(64), maxResps(6){
  nodeArr = new Node[chatSize];
  edgeArr = new Edge[chatSize * maxResps];
}

Chatter::~Chatter(){
  delete[] nodeArr;
  delete[] chatArr;
}


char* Chatter::print(int n){
  return "hi";
}

int Chatter::addResponse(int id, char* line, int next){
  Node* curr = &nodeArr[id];
  // Checks that the node exists in the chat
  if (id < chatSize && nodeID >= 0){
    curr->next[resps++].line = line;
  }

}
