#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#include "game.h"

typedef struct Ball {
    char character;
    int  y, x;
    int  verti_dir, hori_dir;
} BALL;

BALL create_ball(WINDOW *window) {
    BALL ball;
    ball.character = 'O';
    ball.y         = rand() % getmaxy(window) - 1 + 1;
    ball.x         = (getmaxx(window) - 1) / 2;
    ball.verti_dir = ball.hori_dir = 1;
    return ball;
}

void reset_ball(WINDOW *window, BALL *ball) {
    ball->y = rand() % getmaxy(window) - 1 + 1;
    ball->x = (getmaxx(window) - 1) / 2;
}

void draw_ball(WINDOW *window, BALL ball) {
    if((mvwinch(window, ball.y, ball.x) & A_CHARTEXT) == ' ')
        mvwaddch(window, ball.y, ball.x, ball.character);
}

void erase_ball(WINDOW *window, BALL ball) {
    if((mvwinch(window, ball.y, ball.x) & A_CHARTEXT) == (unsigned) ball.character)
        mvwaddch(window, ball.y, ball.x, ' ');
}

void ball_move(WINDOW *window, BALL *ball, int *score, char player_char) {
    erase_ball(window, *ball);
    int projected_y = ball->y + 1 * ball->verti_dir;
    int projected_x = ball->x + 1 * ball->hori_dir;
    
    if(projected_y + 1 >= getmaxy(window) || projected_y <= getbegy(window))
        ball->verti_dir = -ball->verti_dir;
    if(projected_x <= getbegx(window)) {
        reset_ball(window, ball);
        score[1]++;
        display_score(window, score);
    }
    if(projected_x + 1 >= getmaxx(window)) {
        reset_ball(window, ball);
        score[0]++;
        display_score(window, score);
    }

    if((mvwinch(window, projected_y, projected_x) & A_CHARTEXT) == (unsigned) player_char)
        ball->hori_dir = -ball->hori_dir;

    ball->y += 1 * ball->verti_dir;
    ball->x += 1 * ball->hori_dir;
    draw_ball(window, *ball);
}
