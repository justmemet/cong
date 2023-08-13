#include <curses.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdbool.h>

#define draw_ball(window, ball)   draw_obj(window, (ball).y, (ball).x, (ball).character);
#define draw_paddle(window, p) draw_obj(window, (p).y, (p).x, (p).character);

#define create_player(window)  create_paddle(window, (getmaxy(window) - 1) / 2, getbegx(window) + 5);
#define create_enemy(window)   create_paddle(window, (getmaxy(window) - 1) / 2, getmaxx(window) - 5);

typedef struct Paddle {
    char character;
    int y, x;
} PADDLE;

typedef struct Ball {
    char character;
    int y, x, y_velocity, x_velocity;
} BALL;

PADDLE create_paddle(WINDOW *window, int y, int x) {
    PADDLE p;
    p.character = '|';
    p.y = y;
    p.x = x;
    return p;
}

BALL create_ball(WINDOW *window) {
    BALL ball;
    ball.character = 'O';
    ball.y = (getmaxy(window) - 1) / 2;
    ball.x = (getmaxx(window) - 1) / 2;
    ball.y_velocity = ball.x_velocity = 1;
    return ball;
}

void draw_obj(WINDOW *window, int y, int x, char character) {
    mvwaddch(window, y, x, character);
    wrefresh(window);
}

void ball_move(WINDOW *window, BALL *ball) {
    mvwaddch(window, ball->y, ball->x, ' ');
    if(ball->y + 2 == getmaxy(window) || ball->y - 1 == getbegy(window)) ball->y_velocity = -ball->y_velocity;
    if(ball->x + 2 == getmaxx(window) || ball->x - 1 == getbegx(window)) ball->x_velocity = -ball->x_velocity; 
    ball->y += ball->y_velocity;
    ball->x += ball->x_velocity;
    draw_ball(window, *ball);
}

void player_move(WINDOW *window, PADDLE *player, chtype key) {
    mvwaddch(window, player->y, player->x, ' ');
    const chtype UP = 119, DOWN = 115;
    switch(key) {
        case UP:
            if(player->y - 1 != getbegy(window)) player->y--;
            break;
        case DOWN:
            if(player->y + 2 != getmaxy(window)) player->y++;
            break;
    }
    draw_paddle(window, *player);
}

void start_curses() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
}

void init_window(WINDOW *window) {
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

    while(true) {
        chtype key = wgetch(window);
        player_move(window, &player, key);
        ball_move(window, &ball);
        napms(40);
    }

    getch();
    endwin();
    return 0;
}