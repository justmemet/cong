#include <ncurses.h>

typedef struct Ball {
    char character;
    int  y, x;
    int  verti_dir, hori_dir;
} BALL;

BALL create_ball(WINDOW *window) {
    BALL ball;
    ball.character = 'O';
    ball.y         = (getmaxy(window) - 1) / 2 - 1;
    ball.x         = (getmaxx(window) - 1) / 2;
    ball.verti_dir = ball.hori_dir = 1;
    return ball;
}

void draw_ball(WINDOW *window, BALL ball) {
    if((mvwinch(window, ball.y, ball.x) & A_CHARTEXT) == ' ')
        mvwaddch(window, ball.y, ball.x, ball.character);
}

void clear_ball(WINDOW *window, BALL ball) {
    if((mvwinch(window, ball.y, ball.x) & A_CHARTEXT) == (unsigned int) ball.character)
        mvwaddch(window, ball.y, ball.x, ' ');
}

void ball_move(WINDOW *window, BALL *ball, int player_char) {
    clear_ball(window, *ball);
    int correct_y = ball->y + 1 * ball->verti_dir;
    int correct_x = ball->x + 1 * ball->hori_dir;
    
    if(correct_y + 1 >= getmaxy(window) || correct_y <= getbegy(window))
        ball->verti_dir = -ball->verti_dir;
    if(correct_x + 1 >= getmaxx(window) || correct_x <= getbegx(window))
        ball->hori_dir = -ball->hori_dir;

    if((mvwinch(window, correct_y, correct_x) & A_CHARTEXT) == (unsigned) player_char)
        ball->hori_dir = -ball->hori_dir;

    ball->y += 1 * ball->verti_dir;
    ball->x += 1 * ball->hori_dir;
    draw_ball(window, *ball);
}
