/* Chatter.c
 * Owen Monsma
 * 25 April 2017
 */

#include "Chatter.hpp"
#include <fstream>

Chatter::Chatter(){

}

Chatter::~Chatter(){

}

Chatter::Node::Node(){
  nodeID = -1;
  resps = 0;
  line = "";

}

Chatter::Resp::Resp(){
  line = "";
  next = 0;
}

std::string Chatter::print(int n){
  if (n >= 0 && n < CHAT_SIZE && nodeArr[n].nodeID != -1){
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

int Chatter::removeNode(int id){
  // if the node exists
  if (nodeExists(id)){
    // reset data
    nodeArr[id].nodeID = -1;
    nodeArr[id].line = "";
    nodeArr[id].resps = 0;

    return id;
  }
  // node does not exist
  return -1;
}

int Chatter::addResp(int nodeID, std::string line, int next){
  // checks that target node exists
  if (nodeExists(nodeID)){
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

int Chatter::removeResp(int nodeID, int respID){
  if (nodeExists(nodeID)){
    Node* tmp = &nodeArr[nodeID];
    if (respID >= 0 && respID < tmp->resps){
      // moves each response forward to replace the removed response
      for (int i = respID; i < tmp->resps; i++){
        tmp->next[i] = tmp->next[i + 1];
      }
      tmp->resps--;
      return tmp->resps;
    }
    return -1;
  }
  return -1;
}

void Chatter::saveChat(std::string filename){
  std::ofstream ofs(filename);
  boost::archive::text_oarchive oa(ofs);
  oa << *this;
}

void Chatter::loadChat(std::string filename){
  std::ifstream ifs(filename);
  boost::archive::text_iarchive ia(ifs);
  ia >> *this;
}

bool Chatter::nodeExists(int id){
  return (id >= 0 && id < CHAT_SIZE && nodeArr[id].nodeID != -1);
}
