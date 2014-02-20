#include "window.h"

Window::Window(int width, int height, int startx /*= 0*/, int starty /*= 0*/)
    : window_(newwin(height, width, starty, startx)) {
}

Window::~Window() {
  // clear the edges and corners
  wborder(window_, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
  wrefresh(window_);
  delwin(window_);
}

void Window::redraw() const {
  wborder(window_, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
  wattron(window_, COLOR_PAIR(color_));
  box(window_, 0, 0);
  wattroff(window_, COLOR_PAIR(color_));
  wrefresh(window_);
}

