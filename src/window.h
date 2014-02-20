#ifndef _SLEEPYBIRD_WINDOW_H_
#define _SLEEPYBIRD_WINDOW_H_

#include "color.h"

#include <ncurses.h>

class Window {
 public:
  Window(int width, int height, int startx = 0, int starty = 0);
  ~Window();

  WINDOW* window() const { return window_; }

  void activate() {
    color_ = color::ACTIVE;
    redraw();
  }

  void deactivate() {
    color_ = color::INACTIVE;
    redraw();
  }

 private:
  void redraw() const;

  WINDOW* window_;
  color::ID color_;
};

#endif
