/*
 * Owen Monsma
 * ChatNode.hpp
 * 19 April 2017
 */

#ifndef ChatNode_hpp
#define ChatNode_hpp

#include <string>
#include "ChatEdge.hpp"

namespace Chatter{
  class ChatEdge;
  class ChatNode{
  public:
    ChatNode();
    ~ChatNode();

    std::string getLine(){ return line; }
    void setLine(std::string l);

    void addResp(ChatEdge* r);
    int getNumResp(){ return numResp; }

    ChatEdge* respond(int option);

  private:
    std::string line;
    ChatEdge** responses;
    int numResp;
    const int maxResp;
  };

}

#endif /* ChatNode_hpp */
