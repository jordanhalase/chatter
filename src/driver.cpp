#include <stdio.h>

#include "Chatter.hpp"

void setupTestChat(Chatter* chat, std::string filename)
{
  int node0 = chat->addNode("First node!");
  int node1 = chat->addNode("result 1.");
  int node2 = chat->addNode("result 2.");
  int respTo1 = chat->addResp(0, "go to result 1", 1);
  int respTo2 = chat->addResp(0, "go to result 2", 2);

  chat->addResp(1, "go home", 0);
  chat->addResp(2, "go home", 0);

  chat->saveChat(filename);
  printf("Saving out.\n");
}

void loadTestChat(Chatter* chat, std::string filename)
{
  try {
    chat->loadChat(filename);
  } catch (std::exception ex) {
    fprintf(stderr, "Could not load file %s\n", filename.c_str());
    abort();
  }
  printf("Loading in.\n");
}

int main(int argc, char* argv[])
{
  std::string filename = "save";
  if (argc > 1) {
    filename = argv[1];
  }

  Chatter* chat;

  chat = new Chatter();
  setupTestChat(chat, filename);
  delete chat;

  chat = new Chatter();
  loadTestChat(chat, filename);
  chat->chat();
  delete chat;

  return 0;
}
