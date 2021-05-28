#include "pawn.hpp"
#include "queen.hpp"
#include "board.hpp"
#include "human.hpp"
#include "computer.hpp"

#include <iostream>


int main(int argc, char* argv[])
{
    Position start_pos, end_pos;
    std::shared_ptr<Chessman> changing;
    Board b;
    std::shared_ptr<Human> p1 = std::make_shared<Human> (true, b.getBoard());
    std::shared_ptr<Human> p2 = std::make_shared<Human> (false, b.getBoard());
    std::shared_ptr<Player> currentTurn, opponent;
    char x;
    int y;
    int flagQueen = 0;

    if (p1->isWhiteSide()) 
    {
        currentTurn = p1;
        opponent = p2;
    } else 
    {
        currentTurn = p2;
        opponent = p1;
    }

    while(true)
    {
        b.showBoard();
        std::cout << "Which piece you want to move? ";
        std::cin >> x >> y;
        start_pos = start_pos.translateMove(x,y);

        if(b.getBoard()[start_pos.column][start_pos.row] != nullptr)
        {
            if ( b.getBoard()[start_pos.column][start_pos.row]->getWhite() == currentTurn->isWhiteSide() )
            {
                std::cout << "Where to move the piece? ";
                std::cin >> x >> y;
                end_pos = end_pos.translateMove(x,y);

                if (b.getBoard()[start_pos.column][start_pos.row]->makeMove(end_pos, b.getBoard(), flagQueen, opponent->getPieceNum()))
                {
                    std::swap(b.changePiece(end_pos.column, end_pos.row), b.changePiece(start_pos.column, start_pos.row));

                    if (flagQueen == 1)
                    {
                        b.changePiece(end_pos.column, end_pos.row) = std::make_shared<Queen>(end_pos.column, end_pos.row, currentTurn->isWhiteSide());
                        flagQueen = 0;
                    }

                    if (opponent->getPieceNum() == 0
                        || opponent->isMoveImpossible(b.getBoard()))
                    { 
                        break; 
                    } 

                    if (p1 == currentTurn)
                    {
                        currentTurn = p2;
                        opponent = p1;
                    } else
                    {
                        currentTurn = p1;
                        opponent = p2;
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

    b.showBoard();


    return 0;
}
