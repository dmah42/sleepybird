#include <ncurses.h>

int main() {
  initscr();
  printw("Sleepybird");
  refresh();
  getch();
  endwin();
  return 0;
}
