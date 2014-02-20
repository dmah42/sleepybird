#include "color.h"

#include <assert.h>
#include <ncurses.h>

namespace color {
void initialize() {
  assert(has_colors());
  start_color();
  init_pair(INACTIVE, COLOR_WHITE, COLOR_BLACK);
  init_pair(ACTIVE, COLOR_RED, COLOR_BLACK);
}
}  // end namespace color
