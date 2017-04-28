/* Chatter.h
 * Owen Monsma
 * 25 April 2017
 */

#ifndef Chatter_hpp
#define Chatter_hpp

#include <string>
#include <iostream>

#define CHAT_SIZE 64
#define MAX_RESPS 6

class Chatter{
public:
  Chatter();
  ~Chatter();

  Chatter(char* file);

  /** Returns formatted string for specified node ID */
  std::string print(int n);

  /** Adds a new conversation node and returns its ID or -1 on fail */
  int addNode(std::string line);

  /** Adds a new response to the specified node ID or -1 on fail */
  int addResp(int id, std::string line, int next);

  void chat();

private:

  int numNodes;
  int numResps;

  typedef struct Node {
    int nodeID;
    std::string line;
    int resps = 0;
    int next[MAX_RESPS];
  } Node;

  typedef struct Resp {
    int respID;
    std::string line;
    int next;
  } Resp;

  Node* nodeArr;
  Resp* respArr;


};

#endif
