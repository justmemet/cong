#include <ncurses.h>

#include "ball.h"
#include "paddle.h"

void start_curses() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
}

void init_window(WINDOW *window) {
    keypad(window, true);
    nodelay(window, true);
    box(window, 0, 0);
    wmove(window, 1, 2);
    wrefresh(window);
}

int main() {
    start_curses();
    WINDOW *window = stdscr;
    init_window(window);

    BALL ball = create_ball(window);
    draw_ball(window, ball);

    PADDLE player = create_paddle((getmaxy(window) - 1) / 2, getbegx(window));
    draw_paddle(window, player);

    PADDLE bot = create_paddle((getmaxy(window) - 1) / 2, getmaxx(window));
    draw_paddle(window, bot);

    // game loop
    while(true) {
        control_paddle(window, &player, wgetch(window));
        ball_move(window, &ball);
        bot_move(window, &bot, ball);
        wrefresh(window);
        napms(40);
    }

    endwin();
    return 0;
}
