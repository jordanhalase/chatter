#ifndef Timeline_hpp
#define Timeline_hpp

#include <ncurses.h>
#include "UIElement.hpp"
#include "Chatter.hpp"

class Timeline : public UIElement
{
  public:
    Timeline(Chatter*);
    virtual ~Timeline();

    virtual void update();

    int frameLeft();
    int frameRight();
    void goToFrame(const int frame);
    void setNextFramePos(const int frame);

  private:
    WINDOW* el_timeline;
    Chatter* chat;

    int currFrame;
    int nextFrame;

    void moveCurrFrame(const int newFrame);

};

#endif /* Timeline_hpp */
