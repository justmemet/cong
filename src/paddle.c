#include <ncurses.h>
#include <stdlib.h>
#include "ball.h"

typedef struct Paddle {
    char character;
    int  height, width, y, x;
} PADDLE;

PADDLE create_paddle(char character, int height, int width, int y, int x) {
    PADDLE paddle;
    paddle.character = character;
    paddle.height    = height;
    paddle.width     = width;
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

static void get_paddle_parts_posi(PADDLE paddle, int *paddle_top, int *paddle_center, int *paddle_bottom) {
    *paddle_top    = paddle.y;
    *paddle_center = paddle.y + paddle.height / 2;
    *paddle_bottom = paddle.y + paddle.height;
}

void detect_ball_collision(PADDLE paddle, BALL *ball) {
    int proj_y, proj_x;
    int paddle_top, paddle_center, paddle_bottom;
    ball_projection(*ball, &proj_y, &proj_x);
    get_paddle_parts_posi(paddle, &paddle_top, &paddle_center, &paddle_bottom);

    if(ball->x < 10)
        proj_x--;

    int paddle_top_distance = proj_y - paddle_top;
    int paddle_center_distance = proj_y - paddle_center;
    int paddle_bottom_distance = proj_y - paddle_bottom;

    if(proj_x == paddle.x) {
        if(paddle_top_distance >= -1 && paddle_top_distance <= 2) {
            ball->hori_dir = -ball->hori_dir;
            ball->verti_dir = -1;
        }
        if(paddle_center_distance >= -2 && paddle_center_distance <= 2) {
            ball->hori_dir = -ball->hori_dir;
        }
        if(paddle_bottom_distance >= -2 && paddle_bottom_distance <= 0) {
            ball->hori_dir = -ball->hori_dir;
            ball->verti_dir = 1;
        }
    }
}

void control_paddle(WINDOW *window, PADDLE *paddle, chtype key) {
    if(key == KEY_UP || key == KEY_DOWN) {
        clear_paddle(window, *paddle);
        int paddle_top, _, paddle_bottom;
        get_paddle_parts_posi(*paddle, &paddle_top, &_, &paddle_bottom);
        switch(key) {
            case KEY_UP:
                if(paddle_top - 1 != getbegy(window))
                    paddle->y--;
                break;
            case KEY_DOWN:
                if(paddle_bottom + 1 != getmaxy(window))
                    paddle->y++;
                break;
        }
        draw_paddle(window, *paddle);
    }
}

void bot_move(WINDOW *window, PADDLE *bot, BALL ball) {
    if(abs(bot->x - ball.x) < getmaxx(window) / 3) {
        clear_paddle(window, *bot);
        int bot_top, bot_bottom, bot_center;
        get_paddle_parts_posi(*bot, &bot_top, &bot_center, &bot_bottom);
        if(ball.y < bot_center
            && bot_top - 1 != getbegy(window))
            bot->y--;
        if(ball.y > bot_center
            && bot_bottom + 1 != getmaxy(window))
            bot->y++;
        draw_paddle(window, *bot);
    }
}
