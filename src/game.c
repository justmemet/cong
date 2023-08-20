#include <ncurses.h>

void init_curses() {
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

void draw_middle_line(WINDOW *window) {
    for(int i = 1; i < getmaxy(window) - 1; i++)
        mvwaddch(window, getbegy(stdscr)+i, getmaxx(window) / 2, '|');
}

void display_score(WINDOW *window, int *score) {
    mvwaddch(window, getbegy(window) + 3, getbegx(window) + (getmaxx(window) / 4), (char)score[0]+'0');
    mvwaddch(window, getbegy(window) + 3, getmaxx(window) - (getmaxx(window) / 4), (char)score[1]+'0');
}
