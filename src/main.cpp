#include <gui.hpp>

int main()
{
    /* Initialize gameboard */
    init_board();

    /* Setup ncurses */
    initialize_curses();
    refresh();

    draw_board();
    refresh();
    // getch();

    bool invalid_move = true;

    while (invalid_move)
    {
        handle_cursor();
    }

    // clean up curses
    safe_exit();

    return 0;
}
