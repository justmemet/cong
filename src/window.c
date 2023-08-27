#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

void init_game_window(WINDOW *window) {
    keypad(window, true);
    nodelay(window, true);
    box(window, '|', '-');
    wmove(window, 1, 2);
}

void draw_middle_line(WINDOW *window) {
    for(int i = 1; i < getmaxy(window) - 1; i++)
        mvwaddch(window, getbegy(window)+i, getmaxx(window) / 2, '|');
}

void display_score(WINDOW *window, int *score) {
    char *player_a_text = "Player Score";
    char *player_b_text = "Bot Score";

    int y = getbegy(window) + 3;
    int player_a_x = getbegx(window) + getmaxx(window) / 4;
    int player_b_x = getmaxx(window) - getmaxx(window) / 4;

    mvwprintw(window, y - 1, player_a_x - strlen(player_a_text) / 2, player_a_text);
    mvwprintw(window, y - 1, player_b_x - strlen(player_b_text) / 2, player_b_text);

    mvwaddch(window, y, player_a_x, (char)score[0]+'0');
    mvwaddch(window, y, player_b_x, (char)score[1]+'0');
}
