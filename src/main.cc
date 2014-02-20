#include <ncurses.h>

#include <iostream>
#include <map>

#include "color.h"
#include "window.h"

enum WindowID {
  WINDOW_HOME = 0,
  WINDOW_REPLY,
  WINDOW_DM
};

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
  // TODO: pad for internal scrollable data.
  windows[WINDOW_HOME].activate();
  windows[WINDOW_REPLY].deactivate();
  windows[WINDOW_DM].deactivate();

  wmove(prompt_window.window(), 1, 1);
  wmove(windows[WINDOW_HOME].window(), 1, 1);
  wmove(windows[WINDOW_REPLY].window(), 1, 1);
  wmove(windows[WINDOW_DM].window(), 1, 1);

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

      case '\n':
      case KEY_SEND:
      case KEY_ENTER: {
        wprintw(windows[active_window].window(), "%s\n", input.c_str());
        int y, x;
        getyx(windows[active_window].window(), y, x);
        wmove(windows[active_window].window(), y, 1);
        wrefresh(windows[active_window].window());
        input.clear();
        wmove(prompt_window.window(), 1, 1);
        wclrtoeol(prompt_window.window());
        wrefresh(prompt_window.window());
        break;
      }

      case KEY_BACKSPACE: {
        if (!input.empty())
          input.pop_back();
        // TODO: fix the border redraw issue.
        /*
        int y, x;
        getyx(prompt_window.window(), y, x);
        mvwdelch(prompt_window.window(), y, std::max(1, x-1));
        */
        wdelch(prompt_window.window());
        mvwprintw(prompt_window.window(), 1, 1, "%s", input.c_str());
        wrefresh(prompt_window.window());
        break;
      }

      case KEY_UP:
      case KEY_DOWN:
        break;

      default:
        if (input.size() < 140) {
          input += ch;
          mvwprintw(prompt_window.window(), 1, 1, "%s", input.c_str());
          wrefresh(prompt_window.window());
        }
        break;
    }
    prompt_window.deactivate();
  }

  refresh();
  endwin();
  return 0;
}
