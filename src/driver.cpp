#include <iostream>

#include "Chatter.hpp"

void setupTestChat(Chatter* chat);
void loadTestChat(Chatter* chat);

int main(int argc, char* argv[]){
  Chatter testChat = Chatter();
  setupTestChat(&testChat);

  Chatter loadedChat = Chatter();

  loadTestChat(&loadedChat);

  loadedChat.chat();
  return 0;
}

void setupTestChat(Chatter* chat){
  int node0 = chat->addNode("First node!");
  int node1 = chat->addNode("result 1.");
  int node2 = chat->addNode("result 2.");
  int respTo1 = chat->addResp(0, "go to result 1", 1);
  int respTo2 = chat->addResp(0, "go to result 2", 2);

  chat->addResp(1, "go home", 0);
  chat->addResp(2, "go home", 0);

  chat->saveChat("../save/save1");
  std::cout << "Saving out." << std::endl;
}

void loadTestChat(Chatter* chat){
  chat->loadChat("../save/save1");
  std::cout << "Loading in." << std::endl;
}
