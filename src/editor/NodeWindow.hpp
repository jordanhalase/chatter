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
  void setNode(int n);

private:
  WINDOW* el_node;
  Chatter* chat;

  Chatter::Node* showing;
};

#endif /* NodeWindow_hpp */
