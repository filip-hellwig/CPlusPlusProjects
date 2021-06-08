#include "board.hpp"

Board::Board()
{
    /* Inicializacja planszy */
    for (int i = 0; i < 8; i++)
    {
        std::vector<std::shared_ptr<Chessman>> v;

        for (int j = 0; j < 8; j++) {
            v.push_back(nullptr);
        }

        board.push_back(v);
    }

    /* Przypisanie odpowiednich pionków */
    board[0][0] = std::make_shared<Pawn>(0,0,true);
    board[1][1] = std::make_shared<Pawn>(1,1,true);
    board[2][0] = std::make_shared<Pawn>(2,0,true);
    board[3][1] = std::make_shared<Pawn>(3,1,true);
    board[4][0] = std::make_shared<Pawn>(4,0,true);
    board[5][1] = std::make_shared<Pawn>(5,1,true);
    board[6][0] = std::make_shared<Pawn>(6,0,true);
    board[7][1] = std::make_shared<Pawn>(7,1,true);

    board[0][6] = std::make_shared<Pawn>(0,6,false);
    board[1][7] = std::make_shared<Pawn>(1,7,false);
    board[2][6] = std::make_shared<Pawn>(2,6,false);
    board[3][7] = std::make_shared<Pawn>(3,7,false);
    board[4][6] = std::make_shared<Pawn>(4,6,false);
    board[5][7] = std::make_shared<Pawn>(5,7,false);
    board[6][6] = std::make_shared<Pawn>(6,6,false);
    board[7][7] = std::make_shared<Pawn>(7,7,false);
}

void Board::resetBoard()
{
    /* Nullowanie wskażników */
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++) {
            board[j][i] = nullptr;
        }
    }

    /* Przypisanie odpowiednich pionków */
    board[0][0] = std::make_shared<Pawn>(0,0,true);
    board[1][1] = std::make_shared<Pawn>(1,1,true);
    board[2][0] = std::make_shared<Pawn>(2,0,true);
    board[3][1] = std::make_shared<Pawn>(3,1,true);
    board[4][0] = std::make_shared<Pawn>(4,0,true);
    board[5][1] = std::make_shared<Pawn>(5,1,true);
    board[6][0] = std::make_shared<Pawn>(6,0,true);
    board[7][1] = std::make_shared<Pawn>(7,1,true);

    board[0][6] = std::make_shared<Pawn>(0,6,false);
    board[1][7] = std::make_shared<Pawn>(1,7,false);
    board[2][6] = std::make_shared<Pawn>(2,6,false);
    board[3][7] = std::make_shared<Pawn>(3,7,false);
    board[4][6] = std::make_shared<Pawn>(4,6,false);
    board[5][7] = std::make_shared<Pawn>(5,7,false);
    board[6][6] = std::make_shared<Pawn>(6,6,false);
    board[7][7] = std::make_shared<Pawn>(7,7,false);
}

std::vector<std::vector<std::shared_ptr<Chessman>>>& Board::getBoard()
{
    return board;
}

std::shared_ptr<Chessman>& Board::changePiece(int column, int row)
{
    return board[column][row];
}
