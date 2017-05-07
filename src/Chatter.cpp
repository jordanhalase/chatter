/* Chatter.c
 * Owen Monsma
 * 25 April 2017
 */

#include "Chatter.hpp"

Chatter::Chatter(){
  nodeArr = new Node[CHAT_SIZE];

}

Chatter::~Chatter(){
  delete[] nodeArr;
}

Chatter::Node::Node(){
  nodeID = -1;
  resps = 0;
  next = new Resp[MAX_RESPS];
}

Chatter::Node::~Node(){
  delete[] next;
}

std::string Chatter::print(int n){
  if (n >= 0 && nodeArr[n].nodeID != -1){
    Node* tmp = &nodeArr[n];
    std::string ret = tmp->line + "\n";
    for (int i = 0; i < tmp->resps; i++){
      ret += std::to_string(i + 1) + ". " + tmp->next[i].line + "\n";
    }
    return ret;
  }
  return "Invalid node.\n";
}

void Chatter::chat(){
  int curr = 0;
  bool chatting = true;
  while (chatting){
    std::cout << this->print(curr) << std::endl;
    int choice = -1;
    while (choice < 0 || choice > nodeArr[curr].resps){
      std::cin >> choice;
    }
    curr = nodeArr[curr].next[choice - 1].next;
  }
}

int Chatter::addNode(std::string line){
  // iterates array, inserting node into first empty space
  for (int i = 0; i < CHAT_SIZE; i++){
    // empty node slot
    if (nodeArr[i].nodeID == -1){
        nodeArr[i].nodeID = i;
        nodeArr[i].line = line;
        // std::cout << "added node at " << i << std::endl;
        return i;
    }
  }
  return -1;
}

int Chatter::addResp(int nodeID, std::string line, int next){
  // checks that target node exists
  if (nodeID >= 0 && nodeID < CHAT_SIZE && nodeArr[nodeID].nodeID != -1){
    Node* tmp = &nodeArr[nodeID];
    // checks that node has room for a response
    if (tmp->resps < MAX_RESPS){
      tmp->next[tmp->resps].line = line;
      tmp->next[tmp->resps].next = next;

      std::cout << "Added resp " << tmp->resps << " to node " << nodeID << std::endl;

      return tmp->resps++;
    }
  }
  return -1;
}
