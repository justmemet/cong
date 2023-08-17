#include <ncurses.h>

typedef struct Ball {
    char character;
    int  y, x, yvel, xvel;
} BALL;

BALL create_ball(WINDOW *window) {
    BALL ball;
    ball.character = 'O';
    ball.y         = (getmaxy(window) - 1) / 2;
    ball.x         = (getmaxx(window) - 1) / 2;
    ball.yvel      = ball.xvel = 1;
    return ball;
}

void draw_ball(WINDOW *window, BALL ball) {
    mvwaddch(window, ball.y, ball.x, ball.character);
}

void clear_ball(WINDOW *window, BALL ball) {
    mvwaddch(window, ball.y, ball.x, ' ');
}

void ball_move(WINDOW *window, BALL *ball) {
    if((mvwinch(window, ball->y, ball->x) & A_CHARTEXT) == (unsigned int) ball->character)
        clear_ball(window, *ball);

    if(ball->y + 2 == getmaxy(window) || ball->y - 1 == getbegy(window))
        ball->yvel = -ball->yvel;
    if(ball->x + 2 == getmaxx(window) || ball->x - 1 == getbegx(window))
        ball->xvel = -ball->xvel;

    if((mvwinch(window, ball->y, ball->x) & A_CHARTEXT) != ' ') 
        ball->xvel = -ball->xvel;

    ball->y += ball->yvel;
    ball->x += ball->xvel;

    if((mvwinch(window, ball->y, ball->x) & A_CHARTEXT) == ' ')
        draw_ball(window, *ball);
}
