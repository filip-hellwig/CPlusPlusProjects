#include "bishop.hpp"
#include "king.hpp"
#include "knight.hpp"
#include "pawn.hpp"
#include "queen.hpp"
#include "rook.hpp"
#include "board.hpp"
#include "human.hpp"
#include "computer.hpp"

#include <iostream>


int main(int argc, char* argv[])
{
    Position start_pos, end_pos;
    Board b;
    Human p1(true);
    Human p2(false);
    Player currentTurn;
    char x;
    int y;

    if (p1.isWhiteSide()) 
    {
        currentTurn = p1;
    } else 
    {
        currentTurn = p2;
    }

    while(true)
    {
        while(true)
        {
            b.showBoard();
            std::cout << "Which piece you want to move? ";
            std::cin >> x >> y;
            start_pos = start_pos.translateMove(x,y);

            if(b.getBoard()[start_pos.row][start_pos.column] != nullptr)
            {
                if ( b.getBoard()[start_pos.row][start_pos.column]->getWhite() == currentTurn.isWhiteSide() )
                {
                    std::cout << "Where to move the piece? ";
                    std::cin >> x >> y;
                    end_pos = end_pos.translateMove(x,y);

                    if (b.getBoard()[start_pos.row][start_pos.column]->makeMove(end_pos.row, end_pos.column, b.getBoard()))
                    {
                        b.changePiece(end_pos.row, end_pos.column) = b.changePiece(start_pos.row, start_pos.column);
                        b.changePiece(start_pos.row, start_pos.column) = nullptr;

                        if (p1 == currentTurn)
                        {
                            currentTurn = p2;
                        } else
                        {
                            currentTurn = p1;
                        }
                        continue;
                    } else 
                    {
                        std::cout << "This is invalid move\n";
                    }
                } else
                {
                    std::cout << "You picked wrong color\n";
                }
            } else
            {
                std::cout << "There is no piece\n";
            }
        }
    }


    return 0;
}
