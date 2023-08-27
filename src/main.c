#include <ncurses.h>
#include <stdlib.h>

#include "ball.h"
#include "paddle.h"
#include "window.h"

#define BALL_CHARACTER   'O'
#define BALL_Y           getmaxy(game_window) / 2
#define BALL_X           getmaxx(game_window) / 2
#define BALL_VERTI_DIR   1
#define BALL_HORI_DIR    1

#define PADDLE_CHARACTER '|'
#define PADDLE_HEIGHT    10
#define PADDLE_WIDTH     2

#define PLAYER_Y         getmaxy(game_window) / 2
#define PLAYER_x         getbegx(game_window)

#define ENEMY_Y          getmaxy(game_window) / 2
#define ENEMY_x          getmaxx(game_window)

void init_curses() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
}

void end_curses() {
    clear();
    endwin();
    exit(0);
}

int main() {
    init_curses();
    WINDOW *terminal_screen = stdscr;
    int score[] = {0, 0};

    WINDOW *game_window = terminal_screen;
    init_game_window(game_window);

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

    display_score(game_window, score);
    draw_middle_line(game_window);
    draw_ball(game_window, ball);
    draw_paddle(game_window, player);
    draw_paddle(game_window, bot);
    wrefresh(game_window);

    while(score[0] < 9 && score[1] < 9) {
        control_paddle(game_window, &player, wgetch(game_window));
        bot_move(game_window, &bot, ball);

        ball_move(game_window, &ball, score);
        if(ball.hori_dir < 0)
            detect_ball_collision(player, &ball);
        else if(ball.hori_dir > 0)
            detect_ball_collision(bot, &ball);

        wrefresh(game_window);
        napms(40);
    }

    endwin();
    return 0;
}
