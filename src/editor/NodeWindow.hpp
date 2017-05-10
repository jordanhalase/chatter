#ifndef NodeWindow_hpp
#define NodeWindow_hpp

#include <ncurses.h>
#include "UIElement.hpp"
#include "Chatter.hpp"

class NodeWindow : public UIElement{
public:
  NodeWindow(Chatter* ch, int y);
  ~NodeWindow();

  void update();

private:
  WINDOW* el_node;
  Chatter* chat;

};

#endif /* NodeWindow_hpp */
