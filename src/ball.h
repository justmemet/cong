#pragma once
#include <ncurses.h>

typedef struct Ball {
    char character;
    int  y, x;
    int  verti_dir, hori_dir;
} BALL;

extern BALL create_ball(WINDOW *window);
extern void draw_ball(WINDOW *window, BALL ball);
extern void clear_ball(WINDOW *window, BALL ball);
extern void ball_move(WINDOW *window, BALL *ball, int player_char);
