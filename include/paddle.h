#pragma once
#include <ncurses.h>
#include "ball.h"

typedef struct Paddle {
    char character;
    int  height, width, y, x;
} PADDLE;

extern PADDLE create_paddle(char character, int height, int width, int y, int x);
extern void draw_paddle(WINDOW *window, PADDLE paddle);
extern void clear_paddle(WINDOW *window, PADDLE paddle);

extern void detect_ball_collision(PADDLE paddle, BALL *ball);
extern void control_paddle(WINDOW *window, PADDLE *paddle, chtype key);
extern void bot_move(WINDOW *window, PADDLE *bot, BALL ball);
