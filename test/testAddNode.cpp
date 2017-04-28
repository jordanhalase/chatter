#include <assert.h>

#include <stdio.h>

#include "Chatter.hpp"

int main(int argc, char* argv[]){
  Chatter test;
  int actualID1 = test.addNode("");
  int actualID2 = test.addNode("");

  int expectedID1 = 0;
  int expectedID2 = 1;

  assert(actualID1 == expectedID1);
  assert(actualID2 == expectedID2);

  return 0;
}
