#include <ncurses.h>

#include "ball.h"
#include "game.h"
#include "paddle.h"

#define BALL_CHARACTER   'O'
#define BALL_Y           getmaxy(window) / 2
#define BALL_X           getmaxx(window) / 2
#define BALL_VERTI_DIR   1
#define BALL_HORI_DIR    1

#define PADDLE_CHARACTER '|'
#define PADDLE_HEIGHT    10
#define PADDLE_WIDTH     2

#define PLAYER_Y         getmaxy(window) / 2
#define PLAYER_x         getbegx(window)

#define ENEMY_Y          getmaxy(window) / 2
#define ENEMY_x          getmaxx(window)

int main() {
    init_curses();
    WINDOW *window = stdscr;
    init_window(window);
    int score[] = {0, 0};

    // graphics
    BALL ball = create_ball(
        BALL_CHARACTER,
        BALL_Y,
        BALL_X,
        BALL_VERTI_DIR,
        BALL_HORI_DIR
    );
    PADDLE player = create_paddle(
        PADDLE_CHARACTER,
        PADDLE_HEIGHT,
        PADDLE_WIDTH,
        PLAYER_Y,
        PLAYER_x
    );
    PADDLE bot = create_paddle(
        PADDLE_CHARACTER,
        PADDLE_HEIGHT,
        PADDLE_WIDTH,
        ENEMY_Y,
        ENEMY_x
    );

    display_score(window, score);
    draw_middle_line(window);
    draw_ball(window, ball);
    draw_paddle(window, player);
    draw_paddle(window, bot);
    wrefresh(window);

    // game loop
    while(score[0] < 9 && score[1] < 9) {
        control_paddle(window, &player, wgetch(window));
        bot_move(window, &bot, ball);

        ball_move(window, &ball, score);
        if(ball.hori_dir < 0)
            detect_ball_collision(player, &ball);
        else if(ball.hori_dir > 0)
            detect_ball_collision(bot, &ball);

        wrefresh(window);
        napms(40);
    }

    endwin();
    return 0;
}
