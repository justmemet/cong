#include <curses.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>

#define draw_ball(window, ball)       draw_obj(window, (ball).ypos, (ball).xpos, (ball).character);
#define create_player(window)         create_paddle((getmaxy(window) - 1) / 2, getbegx(window) + 5);
#define create_enemy(window)          create_paddle((getmaxy(window) - 1) / 2, getmaxx(window) - 5);
#define clear_obj(window, ypos, xpos) draw_obj(window, ypos, xpos, ' ')

typedef struct Paddle {
    char character;
    int  height, width, ypos, xpos;
} PADDLE;

typedef struct Ball {
    char character;
    int  ypos, xpos, yvel, xvel;
} BALL;

PADDLE create_paddle(int ypos, int xpos) {
    PADDLE paddle;
    paddle.character = '|';
    paddle.height    = 5;
    paddle.width     = 2;
    paddle.ypos      = ypos - paddle.height / 2;
    paddle.xpos      = xpos;
    return paddle;
}

BALL create_ball(WINDOW *window) {
    BALL ball;
    ball.character = 'O';
    ball.ypos      = (getmaxy(window) - 1) / 2;
    ball.xpos      = (getmaxx(window) - 1) / 2;
    ball.yvel      = ball.xvel = 1;
    return ball;
}

void draw_obj(WINDOW *window, int ypos, int xpos, char character) {
    mvwaddch(window, ypos, xpos, character);
    wrefresh(window);
}

void draw_paddle(WINDOW *window, PADDLE paddle) {
    for(size_t i = 0; i < paddle.height; i++) {
        for(size_t j = 0; j < paddle.width; j++) {
            draw_obj(window, paddle.ypos+i, paddle.xpos+((paddle.xpos > 5) ? -j : j), paddle.character);
        }
    }
}

void clear_paddle(WINDOW *window, PADDLE paddle) {
    for(size_t i = 0; i < paddle.height; i++) {
        for(size_t j = 0; j < paddle.width; j++) {
            clear_obj(window, paddle.ypos+i, paddle.xpos+((paddle.xpos > 5) ? -j : j));
        }
    }
}

void ball_move(WINDOW *window, BALL *ball) {
    clear_obj(window, ball->ypos, ball->xpos);
    if(ball->ypos + 2 == getmaxy(window) || ball->ypos - 1 == getbegy(window)) ball->yvel = -ball->yvel;
    if(ball->xpos + 2 == getmaxx(window) || ball->xpos - 1 == getbegx(window)) ball->xvel = -ball->xvel; 
    ball->ypos += ball->yvel;
    ball->xpos += ball->xvel;
    draw_ball(window, *ball);
}

void player_move(WINDOW *window, PADDLE *player, chtype key) {
    if(key == KEY_UP || key == KEY_DOWN) {
        clear_paddle(window, *player);
        switch(key) {
            case KEY_UP:
                if(player->ypos - (player->height / 2) + 1 != getbegy(window)) player->ypos--;
                break;
            case KEY_DOWN:
                if(player->ypos + (player->height + 1) != getmaxy(window)) player->ypos++;
                break;
        }
        draw_paddle(window, *player);
    }
}

void enemy_move(WINDOW *window, PADDLE *enemy, BALL ball) {
    if(ball.ypos - enemy->height / 2 != enemy->ypos && ball.xvel > 0 && ball.xpos > (getmaxx(window) / 2)) {
        clear_paddle(window, *enemy);
        if(ball.ypos < enemy->ypos + (enemy->height - 2)
            && enemy->ypos - (enemy->height / 2) + 1 != getbegy(window)) enemy->ypos--;
        if(ball.ypos > enemy->ypos + (enemy->height - (enemy->height/2 + 2))
            && enemy->ypos + (enemy->height + 1) != getmaxy(window)) enemy->ypos++;
        draw_paddle(window, *enemy);
    }
}

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

    PADDLE player = create_player(window);
    draw_paddle(window, player);

    PADDLE enemy = create_enemy(window);
    draw_paddle(window, enemy);

    // game loop
    while(true) {
        chtype key = wgetch(window);
        player_move(window, &player, key);
        flushinp();
        ball_move(window, &ball);
        enemy_move(window, &enemy, ball);
        napms(40);
    }

    endwin();
    return 0;
}