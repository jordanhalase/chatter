#include "Timeline.hpp"

Timeline::Timeline(Chatter* chat)
{
  el_timeline = newwin(2, COLS, LINES - 2, 0);
  wbkgd(el_timeline, COLOR_PAIR(2));
  this->chat = chat;
  currFrame = 0;
}

Timeline::~Timeline()
{
  delwin(el_timeline);
}

void Timeline::update()
{
  // moves cursor to start of window
  wmove(el_timeline, 0, 0);
  // iterates the chat and prints character for each node
  for (int i = 0; i < CHAT_SIZE; i++) {
    Chatter::Node* tmp = chat->getNode(i);
    if (tmp->nodeID != -1) {
      waddch(el_timeline, '!');
    } else {
      waddch(el_timeline, '*');
    }
  }

  moveCurrFrame(0);

  wrefresh(el_timeline);
}

int Timeline::frameLeft()
{
  moveCurrFrame(currFrame - 1);
  return currFrame;
}

int Timeline::frameRight()
{
  moveCurrFrame(currFrame + 1);
  return currFrame;
}

void Timeline::setNextFramePos(const int frame)
{
  if (frame >= 0 && frame < CHAT_SIZE && frame != currFrame) {
    if (nextFrame != currFrame) {
      wmove(el_timeline, 1, nextFrame);
      waddch(el_timeline, ' ');
    }
    nextFrame = frame;
    wmove(el_timeline, 1, nextFrame);
    waddch(el_timeline, '$');
    wrefresh(el_timeline);
  }
}

void Timeline::goToFrame(const int frame)
{
  moveCurrFrame(frame);
}

void Timeline::moveCurrFrame(const int newFrame)
{
  if (newFrame >= 0 && newFrame < CHAT_SIZE) {
    wmove(el_timeline, 1, currFrame);
    waddch(el_timeline, ' ');
    currFrame = newFrame;
    wmove(el_timeline, 1, currFrame);
    waddch(el_timeline, '^');
    wrefresh(el_timeline);
  }
}
