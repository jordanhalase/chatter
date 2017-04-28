#include <iostream>

#include "Chatter.hpp"

void setupTestChat(Chatter* chat);

void main(int argc, char* argv[]){
  Chatter testChat = Chatter();
  setupTestChat(&testChat);
  return 0;
}

void setupTestChat(Chatter* chat){

}
