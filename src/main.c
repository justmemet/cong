#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#include "game.h"
#include "ball.h"
#include "paddle.h"

int main() {
    srand(time(NULL));
    init_curses();
    WINDOW *window = stdscr;
    init_window(window);
    int score[] = {0, 0};

    // graphics
    BALL ball = create_ball(window);
    PADDLE player = create_paddle(
        (getmaxy(window) - 1) / 2,
        getbegx(window)
    );
    PADDLE bot = create_paddle(
        (getmaxy(window) - 1) / 2,
        getmaxx(window)
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
