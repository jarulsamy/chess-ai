#include "gui.hpp"
#include "utils.hpp"

#include <ncurses.h>
#include <string.h>

using namespace window;

WINDOW *w1, *w2, *w3;

Pt::Pt()
{
    x = 0;
    y = 0;
}

Pt::Pt(int x_, int y_)
{
    x = x_;
    y = y_;
}

void initialize_curses()
{
    // Fix locale
    setlocale(LC_ALL, "");
    // start curses
    initscr();
    // enable color
    start_color();

    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    // if (!has_colors() || (start_color() != OK) || COLORS != 256)
    //     error("colors");

    // Define three horizontally-stacked windows:
    //
    //    1 - board window
    //    2 - CLI output window
    //    3 - CLI input window
    //
    int half_height = LINES / 2;

    w1 = newwin(half_height, COLS, 0, 0);
    w2 = newwin(half_height - 1, COLS, half_height, 0);
    w3 = newwin(1, COLS, LINES - 1, 0);

    if (w1 == NULL || w2 == NULL || w3 == NULL)
    {
        waddstr(stdscr, "newwin");
        endwin();
    }

    scrollok(w2, TRUE);

    // initialize color tuples
    //   see http://www.calmar.ws/vim/256-xterm-24bit-rgb-color-chart.html
    // FG, BG
    init_pair(LIGHT_SQUARE, 0, 229);
    init_pair(DARK_SQUARE, 0, 209);
    init_pair(BLUISH, 111, 233);
    init_pair(TERMINAL, 252, 232);
    init_pair(GREENISH, 107, 233);
    init_pair(CLI_INPUT, 253, 232);
    init_pair(GRAY_ON_BLACK, 245, 233);
    init_pair(RED, 1, 52);

    wbkgd(w1, COLOR_PAIR(TERMINAL));
    wbkgd(w2, COLOR_PAIR(TERMINAL));
    wbkgd(w3, COLOR_PAIR(CLI_INPUT));

    wattron(w1, COLOR_PAIR(BLUISH));
    mvwaddstr(w1, 0, centered(N_COLS, TITLE), TITLE);
    wstandend(w1);

    wrefresh(stdscr);
    wrefresh(w1);
    wrefresh(w2);
    wrefresh(w3);

    touchwin(stdscr);
    touchwin(w1);
    touchwin(w2);
    touchwin(w3);
}

void safe_exit()
{
    delwin(w1);
    delwin(w2);
    delwin(w3);
    endwin();

    exit(0);
}

void draw_board()
{
    // Determine the window width and thereby, the proper indentation
    int w_y, w_x, h_indent, v_indent;
    getmaxyx(w1, w_y, w_x);
    h_indent = (w_x - N_ROWS * SQUARE_WIDTH) / 2;
    v_indent = 0;

    CURSOR_MIN.x = h_indent;
    CURSOR_MIN.y = v_indent;

    // Print the board
    for (int row = 0; row < N_ROWS; row++)
    {
        bool black_square = even(row) ? true : false;
        wmove(w1, row + v_indent, h_indent);

        for (int col = 0; col < N_COLS * SQUARE_WIDTH; col++)
        {
            // flip square color at square borders
            if ((col % SQUARE_WIDTH) == 0)
                black_square = !black_square;

            if (black_square)
                wattron(w1, COLOR_PAIR(DARK_SQUARE));
            else
                wattron(w1, COLOR_PAIR(LIGHT_SQUARE));

            if ((col - 1) % 3 == 0)
            {
                int index = col / SQUARE_WIDTH;
                waddstr(w1, board[row][index].c_str());
                getyx(w1, CURSOR_MAX.y, CURSOR_MAX.x);
            }
            else
            {
                waddstr(w1, pieces::EMPTY_SQUARE.c_str());
            }
        }
        waddstr(w1, "\n");
    }

    wmove(w1, CURSOR_MIN.y, CURSOR_MIN.x);
    wrefresh(w1);
}

Pt handle_cursor()
{
    int cX, cY;
    char ch;

    do
    {
        ch = wgetch(w1);
        if (ch == 'q') // Q to exit gracefully
        {
            safe_exit();
        }
        else if (ch == KEY_LEFT || ch == 'h')
        {
            getyx(w1, cY, cX);
            if ((cX - SQUARE_WIDTH) >= CURSOR_MIN.x)
                wmove(w1, cY, cX - SQUARE_WIDTH);
        }
        else if (ch == KEY_RIGHT || ch == 'l')
        {
            getyx(w1, cY, cX);
            if ((cX + SQUARE_WIDTH) <= CURSOR_MAX.x)
                wmove(w1, cY, cX + SQUARE_WIDTH);
        }
        else if (ch == KEY_UP || ch == 'k')
        {
            getyx(w1, cY, cX);
            if ((cY - 1) >= CURSOR_MIN.y)
                wmove(w1, cY - 1, cX);
        }
        else if (ch == KEY_DOWN || ch == 'j')
        {
            getyx(w1, cY, cX);
            if ((cY + 1) <= CURSOR_MAX.y)
                wmove(w1, cY + 1, cX);
        }
        wrefresh(w1);
    } while (ch != ' ');

    getyx(stdscr, cY, cX);
    return Pt(cX, cY);
}
