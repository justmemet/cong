#include <curses.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#define drawball(w, b)      drawobj(w, (b).y, (b).x, (b).ch);
#define drawpaddle(w, p)    drawobj(w, (p).y, (p).x, (p).ch);

typedef struct Paddle {
    char ch;
    int y, x;
} PADDLE;

typedef struct Ball {
    char ch;
    int y, x, yvel, xvel;
} BALL;

PADDLE createplr(WINDOW *w) {
    PADDLE p;
    p.ch = '|';
    p.y = (getmaxy(w) - 1) / 2;
    p.x = getbegx(w) + 5;
    return p;
}

BALL createball(WINDOW *w) {
    BALL b;
    b.ch = 'O';
    b.y = (getmaxy(w) - 1) / 2;
    b.x = (getmaxx(w) - 1) / 2;
    b.yvel = b.xvel = 1;
    return b;
}

void drawobj(WINDOW *w, int y, int x, char ch) {
    mvwaddch(w, y, x, ch);
    wrefresh(w);
}

void ballmov(WINDOW *w, BALL *b) {
    mvwaddch(w, b->y, b->x, ' ');
    if(b->y + 2 == getmaxy(w) || b->y - 1 == getbegy(w)) b->yvel = -b->yvel;
    if(b->x + 2 == getmaxx(w) || b->x - 1 == getbegx(w)) b->xvel = -b->xvel; 
    b->y += b->yvel;
    b->x += b->xvel;
    drawball(w, *b);
}

void plrmov(WINDOW *w, PADDLE *plr, chtype k) {
    mvwaddch(w, plr->y, plr->x, ' ');
    switch(k) {
        case 119:
            if(plr->y - 1 != getbegy(w)) plr->y--;
            break;
        case 115:
            if(plr->y + 2 != getmaxy(w)) plr->y++;
            break;
    }
    drawpaddle(w, *plr);
}

void startnc() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
}

void initwin(WINDOW *w) {
    nodelay(w, true);
    box(w, 0, 0);
    wmove(w, 1, 2);
    wrefresh(w);
}

int main() {
    startnc();
    WINDOW *curwin = stdscr;
    initwin(curwin);

    BALL b = createball(curwin);
    drawball(curwin, b);

    PADDLE plr = createplr(curwin);
    drawpaddle(curwin, plr);

    while(true) {
        chtype k = wgetch(curwin);
        plrmov(curwin, &plr, k);
        ballmov(curwin, &b);
        napms(40);
    }

    getch();
    endwin();
    return 0;
}