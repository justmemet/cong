#include <ctype.h>
#include <ncurses.h>
#include "window.h"

typedef struct Ball {
    char character;
    int  y, x;
    int  verti_dir, hori_dir;
    int  initial_y, initial_x;
} BALL;

BALL create_ball(char character, int y, int x, int verti_dir, int hori_dir) {
    BALL ball;
    ball.character = character;
    ball.initial_y = ball.y = y - 1;
    ball.initial_x = ball.x = x - 1;
    ball.verti_dir = verti_dir;
    ball.hori_dir  = hori_dir;
    return ball;
}

void reset_ball(BALL *ball) {
    ball->y = ball->initial_y;
    ball->x = ball->initial_x;
}

void draw_ball(WINDOW *window, BALL ball) {
    if(isblank(mvwinch(window, ball.y, ball.x) & A_CHARTEXT))
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

static bool detect_roof_collision(WINDOW *window, int proj_y) {
    return proj_y + 1 >= getmaxy(window) || proj_y <= getbegy(window);
}

static bool detect_wall_collision(WINDOW *window, int proj_x) {
    return proj_x + 1 >= getmaxx(window) || proj_x <= getbegx(window);
}

void ball_move(WINDOW *window, BALL *ball, int *score) {
    erase_ball(window, *ball);
    int proj_y;
    int proj_x;
    ball_projection(*ball, &proj_y, &proj_x);
    
    if(detect_roof_collision(window, proj_y))
        ball->verti_dir = -ball->verti_dir;
    if(detect_wall_collision(window, proj_x)) {
        reset_ball(ball);
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
