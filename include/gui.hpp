#ifndef GUI_HPP
#define GUI_HPP

#include <ncurses.h>
#include <stdint.h>
#include <stdlib.h>
#include <string>

#include "game.hpp"

class Pt
{
public:
    Pt();
    Pt(int, int);
    int x;
    int y;
};

namespace pieces
{
    const std::string EMPTY_SQUARE = " ";

    // Black pieces
    const std::string BLACK_R = "♜";
    const std::string BLACK_N = "♞";
    const std::string BLACK_B = "♝";
    const std::string BLACK_Q = "♛";
    const std::string BLACK_K = "♚";
    const std::string BLACK_P = "♟";
    // White pieces
    const std::string WHITE_R = "♖";
    const std::string WHITE_N = "♘";
    const std::string WHITE_B = "♗";
    const std::string WHITE_Q = "♕";
    const std::string WHITE_K = "♔";
    const std::string WHITE_P = "♙";

    const std::string FINGER = "☚";

} // namespace pieces

namespace window
{
    // General constants
    const char TITLE[] = "ASCII Chess";
    // A chess board with n^2 cells where each cell has cell width w and
    // cell height has size (wn+1)(hn+1).
    const int N_ROWS = 8;
    const int N_COLS = 8;
    const int CENTER = N_COLS / 2;
    const int SQUARE_WIDTH = 3;

    static Pt CURSOR_MAX;
    static Pt CURSOR_MIN;
} // namespace window

// color handles, see vichess.c for assignments
enum __CURSES_COLORS
{
    CLI_INPUT,
    TERMINAL,
    LIGHT_ON_DARK,
    GREENISH,
    QUIET_DARK,
    DARK_SQUARE,
    LIGHT_SQUARE,
    GRAY_ON_BLACK,
    BLUISH,
    RED
};

void initialize_curses();
void safe_exit();
void draw_board();
Pt handle_cursor();

#endif
