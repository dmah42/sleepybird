#include <ncurses.h>

#include <iostream>
#include <map>

#include "color.h"
#include "window.h"

int main() {
  initscr();
  color::initialize();  
  // line buffering disabled
  cbreak();
  noecho();

  const int width = (COLS / 3);
  const int height = LINES - 3;

  Window prompt_window(COLS - 1, 3, 0, height);
  Window windows[] = {
    Window(width, height, 0, 0),
    Window(width, height, width, 0),
    Window(width, height, 2 * width, 0)
  };

  keypad(prompt_window.window(), true);
  refresh();

  prompt_window.deactivate();
  windows[0].activate();
  windows[1].deactivate();
  windows[2].deactivate();

  wmove(prompt_window.window(), 1, 1);

  int ch;
  std::string input;
  int active_window = 0;
  while (true) {
    ch = wgetch(prompt_window.window());

    switch (ch) {
      case KEY_LEFT:
        windows[active_window].deactivate();
        active_window = (active_window - 1) % 3;
        windows[active_window].activate();
        break;

      case KEY_RIGHT:
        windows[active_window].deactivate();
        active_window = (active_window + 1) % 3;
        windows[active_window].activate();
        break;

      case KEY_ENTER:
        mvprintw(23, 0, "Would tweet '%s'", input.c_str());
        refresh();
        input.clear();
        wmove(prompt_window.window(), 1, 1);
        break;

      case KEY_BACKSPACE: {
        if (!input.empty())
          input.pop_back();
        int y, x;
        getyx(prompt_window.window(), y, x);
        mvwdelch(prompt_window.window(), y, std::max(1, x-1));
        refresh();
        break;
      }

      case KEY_UP:
      case KEY_DOWN:
        break;

      default:
        waddch(prompt_window.window(), ch);
        refresh();
        input += ch;
        break;
    }
    prompt_window.deactivate();
  }

  refresh();
  endwin();
  return 0;
}
