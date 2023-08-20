#pragma once
#include <ncurses.h>

typedef struct Ball {
    char character;
    int  y, x;
    int  verti_dir, hori_dir;
} BALL;

extern BALL create_ball(WINDOW *window);
extern void reset_ball(WINDOW *window, BALL *ball);
extern void draw_ball(WINDOW *window, BALL ball);
extern void erase_ball(WINDOW *window, BALL ball);
extern void ball_projection(BALL ball, int *proj_y, int *proj_x);
extern void ball_move(WINDOW *window, BALL *ball, int *score);
