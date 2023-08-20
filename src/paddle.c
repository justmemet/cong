#include <ncurses.h>
#include <stdlib.h>
#include "ball.h"

typedef struct Paddle {
    char character;
    int  height, width, y, x;
} PADDLE;

PADDLE create_paddle(int y, int x) {
    PADDLE paddle;
    paddle.character = '|';
    paddle.height    = 10;
    paddle.width     = 2;
    paddle.y         = (y - 1) - paddle.height / 2;
    paddle.x         = x + ((x > 0) ? -(paddle.width + 5) : 5);
    return paddle;
}

void draw_paddle(WINDOW *window, PADDLE paddle) {
    for(int i = 0; i < paddle.height; i++) {
        for(int j = 0; j < paddle.width; j++) {
            mvwaddch(window, paddle.y + i, paddle.x + j, paddle.character);
        }
    }
}

void clear_paddle(WINDOW *window, PADDLE paddle) {
    for(int i = 0; i < paddle.height; i++) {
        for(int j = 0; j < paddle.width; j++) {
            mvwaddch(window, paddle.y + i, paddle.x + j, ' ');
        }
    }
}

void control_paddle(WINDOW *window, PADDLE *paddle, chtype key) {
    if(key == KEY_UP || key == KEY_DOWN) {
        clear_paddle(window, *paddle);
        switch(key) {
            case KEY_UP: {
                int paddle_top_y = paddle->y - 1;
                if(paddle_top_y != getbegy(window))
                    paddle->y--;
                break;
            }
            case KEY_DOWN: {
                int paddle_bottom_y = paddle->y + paddle->height;
                if(paddle_bottom_y + 1 != getmaxy(window))
                    paddle->y++;
                break;
            }
        }
        draw_paddle(window, *paddle);
    }
}

void bot_move(WINDOW *window, PADDLE *bot, BALL ball) {
    if(ball.y - bot->height / 2 != bot->y && abs(bot->x - ball.x) < getmaxx(window) / 3) {
        clear_paddle(window, *bot);
        int bot_top_y    = bot->y - 1, 
            bot_bottom_y = bot->y + bot->height,
            bot_center   = bot->y + bot->height / 2;

        if(ball.y < bot_center
            && bot_top_y != getbegy(window))
            bot->y--;
        if(ball.y > bot_center
            && bot_bottom_y + 1 != getmaxy(window))
            bot->y++;
        draw_paddle(window, *bot);
    }
}
