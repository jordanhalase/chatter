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

  void setLine(const char* str);
  const char* getLine();

  /* Selected line changing */
  int chLineUp();
  int chLineDn();
  int getSelNextLine();

private:
  WINDOW* el_node;
  Chatter* chat;

  Chatter::Node* showing;
  int showingID;

  int lineSel;
  int changeLine(int newL);
};

#endif /* NodeWindow_hpp */
