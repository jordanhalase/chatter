#include <iostream>

#include "Chatter.hpp"

void setupTestChat(Chatter* chat);

int main(int argc, char* argv[]){
  Chatter testChat;
  setupTestChat(&testChat);
  std::cout << testChat.print(0) << std::endl;
  return 0;
}

void setupTestChat(Chatter* chat){
  chat->addNode("The first chat node.");
  chat->addNode("The second chat node.");

  chat->addResp(0, "One response", 1);
  chat->addResp(0, "Two response", 1);
}
