/*
 * Owen Monsma
 * ChatEdge.hpp
 * 19 April 2017
 */

#ifndef ChatEdge_hpp
#define ChatEdge_hpp

#include <string>
#include "ChatNode.hpp"

namespace Chatter{
  class ChatNode;
  class ChatEdge{
  public:
    ChatEdge();
    ~ChatEdge();

    void setNext(ChatNode* n);
    ChatNode* getNext();

    void setLine(std::string l);
    std::string getLine();

    void setExit(bool e);
    bool getExit();

  private:
    std::string line;
    ChatNode* next;
    bool seen;
    bool exitline;
  };
}

#endif /* ChatEdge_hpp */
