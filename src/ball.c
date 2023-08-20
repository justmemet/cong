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

void ball_projection(BALL ball, int *proj_y, int *proj_x) {
    *proj_y = ball.y + 1 * ball.verti_dir;
    *proj_x = ball.x + 1 * ball.hori_dir;
}

static bool detect_verti_collision(WINDOW *window, int proj_y) {
    return proj_y + 1 >= getmaxy(window) || proj_y <= getbegy(window);
}

static bool detect_hori_collision(WINDOW *window, int proj_x) {
    return proj_x + 1 >= getmaxx(window) || proj_x <= getbegx(window);
}

void ball_move(WINDOW *window, BALL *ball, int *score) {
    erase_ball(window, *ball);
    int proj_y;
    int proj_x;
    ball_projection(*ball, &proj_y, &proj_x);
    
    if(detect_verti_collision(window, proj_y))
        ball->verti_dir = -ball->verti_dir;
    if(detect_hori_collision(window, proj_x)) {
        reset_ball(window, ball);
        if(proj_x + 1 >= getmaxx(window))
            score[0]++;
        else if(proj_x <= getbegx(window))
            score[1]++;
        display_score(window, score);
    }

    ball->y += 1 * ball->verti_dir;
    ball->x += 1 * ball->hori_dir;
    draw_ball(window, *ball);
}
