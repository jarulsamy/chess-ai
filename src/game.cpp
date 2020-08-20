#include "game.hpp"
#include "gui.hpp"

using namespace window;

std::string board[N_ROWS][N_COLS];

void init_board()
{
    for (int i = 0; i < N_ROWS; i++)
    {
        for (int j = 0; j < N_COLS; j++)
        {
            board[i][j] = pieces::EMPTY_SQUARE;
        }
    }

    // Black
    board[0][0] = pieces::BLACK_R;
    board[0][1] = pieces::BLACK_N;
    board[0][2] = pieces::BLACK_B;
    board[0][3] = pieces::BLACK_Q;
    board[0][4] = pieces::BLACK_K;
    board[0][5] = pieces::BLACK_B;
    board[0][6] = pieces::BLACK_N;
    board[0][7] = pieces::BLACK_R;

    // Pawns
    for (int i = 0; i < N_COLS; i++)
    {
        board[1][i] = pieces::BLACK_P;
    }

    // White
    board[7][0] = pieces::WHITE_R;
    board[7][1] = pieces::WHITE_N;
    board[7][2] = pieces::WHITE_B;
    board[7][3] = pieces::WHITE_Q;
    board[7][4] = pieces::WHITE_K;
    board[7][5] = pieces::WHITE_B;
    board[7][6] = pieces::WHITE_N;
    board[7][7] = pieces::WHITE_R;

    // Pawns
    for (int i = 0; i < N_COLS; i++)
    {
        board[6][i] = pieces::WHITE_P;
    }
}
