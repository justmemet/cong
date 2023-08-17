#pragma once
#include <ncurses.h>

typedef struct Ball {
    char character;
    int  y, x, yvel, xvel;
} BALL;

extern BALL create_ball(WINDOW *window);
extern void draw_ball(WINDOW *window, BALL ball);
extern void clear_ball(WINDOW *window, BALL ball);
extern void ball_move(WINDOW *window, BALL *ball);
