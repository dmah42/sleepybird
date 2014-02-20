cmake_minimum_required(VERSION 2.6)
set(CURSES_NEED_NCURSES true)
find_package(Curses REQUIRED)

set(CMAKE_CXX_FLAGS "-Wall -Werror -pedantic-errors --std=c++0x -Isrc/ -I${CURSES_INCLUDE_DIR}")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-fno-strict-aliasing -O3 -DNDEBUG")

set(SOURCE_FILES "src/color.cc"
		 "src/main.cc"
		 "src/window.cc")

add_executable(sleepybird ${SOURCE_FILES})
target_link_libraries(sleepybird ${CURSES_LIBRARIES})
install(TARGETS sleepybird RUNTIME DESTINATION bin)
