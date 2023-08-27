#pragma once
#include <ncurses.h>

extern void init_game_window(WINDOW *window);
extern void draw_middle_line(WINDOW *window);
extern void display_score(WINDOW *window, int *score);
