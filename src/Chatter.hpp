/*
 * Owen Monsma
 * Chatter.hpp
 * 19 April 2017
 */

#ifndef Chatter_hpp
#define Chatter_hpp

#include "ChatNode.hpp"
#include "ChatEdge.hpp"

namespace Chatter{
  enum filemode {XML, JSON, BIN};

  class Chatter{
  public:
    Chatter();
    ~Chatter();

    // setup functions
    void loadChat(std::string file, filemode mode);
    void setEntry(ChatNode* e);
    void chat();

    void initTestChat();

  private:
    ChatNode* entry;
    ChatNode* current;
    bool chatting;
  };
}

#endif /* Chatter_hpp */
