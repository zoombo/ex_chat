#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>

/*
 *
 * 
 *  
 */

/* Поскольку в C нету пространств имен (namespaces), то к именам некоторых переменных,
 * кроме самых очевидных (переменные счетчики вроде 'i' в for(int i = 0;...) и т.д.), 
 * я буду добавлять префикс, чтобы имя моей переменной случайно не совпало с 
 * именем какой-нибудь библиотечной переменной.
 * cv - сокр. от current var.
 */

int main(int argc, char **argv) {

    ///_Проводим подготовительные работы_///////////////////////////////////////

    // Инициализируем новый curses-экран.
    initscr();
    // Не выводить нажатые клавиши.
    noecho();
    // Запомним ширину и высоту. 
    int current_width = getmaxx(stdscr);
    int current_height = getmaxy(stdscr);

    box(stdscr, 0, 0);

    WINDOW *users_list = newwin(current_height - 6, current_width / 7, 0, 0);
    box(users_list, 0, 0);

    char pressed_key = ' ';

    ///_Конец подготовительных работ_///////////////////////////////////////////


    while (true) {

        pressed_key = getch();

        if (pressed_key == 'q')
            break;


        if (current_width != getmaxx(stdscr) || current_height != getmaxy(stdscr)) {
            current_width = getmaxx(stdscr);
            current_height = getmaxy(stdscr);
            clear();
            box(stdscr, 0, 0);
        }

        mvwprintw(stdscr, 1, 1, "%d ", current_width);
        mvwprintw(stdscr, 2, 1, "%d ", current_height);

        pressed_key = ' ';
    }

    refresh();
    endwin();
}