/* Chatter.c
 * Owen Monsma
 * 25 April 2017
 */

#include "Chatter.hpp"

Chatter::Chatter(){
  nodeArr = new Node[CHAT_SIZE];
  respArr = new Resp[CHAT_SIZE * MAX_RESPS];

  numNodes = 0;
  numResps = 0;
}

Chatter::~Chatter(){
  delete[] nodeArr;
  delete[] respArr;
}


std::string Chatter::print(int n){
  if (n >= 0 && n < numNodes){
    Node* tmp = &nodeArr[n];
    std::string ret = tmp->line + "\n";
    for (int i = 0; i < tmp->resps; i++){
      ret += std::to_string(i + 1) + ". " + respArr[tmp->next[i]].line + "\n";
    }
    return ret;
  }
  return "Invalid node.\n";
}

int Chatter::addNode(std::string line){
  if (numNodes < CHAT_SIZE){
    nodeArr[numNodes].line = line;
    return numNodes++;
  }
  return -1;
}

int Chatter::addResp(int nodeID, std::string line, int next){
  // Checks for room in respArr, and in the node's responses
  if (numResps < (CHAT_SIZE * MAX_RESPS) && nodeArr[nodeID].resps < MAX_RESPS){
    // Add the response to the response array
    respArr[numResps].line = line;
    respArr[numResps].next = next;
    // Add the response to the specified node
    Node* tmp = &nodeArr[nodeID];
    tmp->next[tmp->resps++] = numResps;

    return numResps++;
  }
  return -1;
}
