#include "board.hpp"

Board::Board()
{
    for (int i = 0; i < 8; i++)
    {
        std::vector<std::shared_ptr<Chessman>> v;

        for (int j = 0; j < 8; j++) {
            v.push_back(nullptr);
        }

        board.push_back(v);
    }

    board[0][0] = std::make_shared<Rook>(0,0,true);
    board[0][1] = std::make_shared<Knight>(1,0,true);
    board[0][2] = std::make_shared<Bishop>(2,0,true);
    board[0][3] = std::make_shared<Queen>(3,0,true);
    board[0][4] = std::make_shared<King>(4,0,true);
    board[0][5] = std::make_shared<Bishop>(5,0,true);
    board[0][6] = std::make_shared<Knight>(6,0,true);
    board[0][7] = std::make_shared<Rook>(7,0,true);
    board[1][0] = std::make_shared<Pawn>(0,1,true);
    board[1][1] = std::make_shared<Pawn>(1,1,true);
    board[1][2] = std::make_shared<Pawn>(2,1,true);
    board[1][3] = std::make_shared<Pawn>(3,1,true);
    board[1][4] = std::make_shared<Pawn>(4,1,true);
    board[1][5] = std::make_shared<Pawn>(5,1,true);
    board[1][6] = std::make_shared<Pawn>(6,1,true);
    board[1][7] = std::make_shared<Pawn>(7,1,true);

    board[7][0] = std::make_shared<Rook>(0,7,false);
    board[7][1] = std::make_shared<Knight>(1,7,false);
    board[7][2] = std::make_shared<Bishop>(2,7,false);
    board[7][3] = std::make_shared<Queen>(3,7,false);
    board[7][4] = std::make_shared<King>(4,7,false);
    board[7][5] = std::make_shared<Bishop>(5,7,false);
    board[7][6] = std::make_shared<Knight>(6,7,false);
    board[7][7] = std::make_shared<Rook>(7,7,false);
    board[6][0] = std::make_shared<Pawn>(0,0,false);
    board[6][1] = std::make_shared<Pawn>(1,6,false);
    board[6][2] = std::make_shared<Pawn>(2,6,false);
    board[6][3] = std::make_shared<Pawn>(3,6,false);
    board[6][4] = std::make_shared<Pawn>(4,6,false);
    board[6][5] = std::make_shared<Pawn>(5,6,false);
    board[6][6] = std::make_shared<Pawn>(6,6,false);
    board[6][7] = std::make_shared<Pawn>(7,6,false);
    
}

void Board::showBoard()
{
    for (int i = 7; i > -1; i--)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j] == nullptr)
            {
                std::cout << " 0  ";
            } else
            {
                std::cout << board[i][j]->name() << " ";
            }
        }
        std::cout << "\n";
    }
}

std::vector<std::vector<std::shared_ptr<Chessman>>> Board::getBoard()
{
    return board;
}

std::shared_ptr<Chessman> Board::changePiece(int row, int column)
{
    return board[row][column];
}
