#include <iostream>

#include "Chatter.hpp"

void setupTestChat(Chatter* chat);

int main(int argc, char* argv[]){
  Chatter testChat = Chatter();
  setupTestChat(&testChat);
  testChat.chat();
  return 0;
}

void setupTestChat(Chatter* chat){
  chat->addNode("First node!");
  chat->addNode("result 1.");
  chat->addNode("result 2");
  chat->addResp(0, "go to result 1", 1);
  chat->addResp(0, "go to result 2", 2);
}
