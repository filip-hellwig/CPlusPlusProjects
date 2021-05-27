#include "pawn.hpp"

bool Pawn::makeMove(Position nextMove, std::vector<std::vector<std::shared_ptr<Chessman>>>& board, int& flagQueen, int& pieceNum)
{
    if ( board[nextMove.column][nextMove.row] != nullptr )
    {  
        if (nextMove != position)
        {
            return false;
        }
    }

    if (checkIndexValidity(nextMove.column, nextMove.row))
    {
        if ( (nextMove.column-position.column == 1 
            || nextMove.column-position.column == -1) 
            && nextMove.row-position.row == 1
            && position.column != nextMove.column
            && position.row != nextMove.row
            && white == true)
        {
            position = nextMove;
            if((nextMove.row == 7 && white == true)
                || (nextMove.row == 0 && white == false))
            {
                flagQueen = 1;
            }
            return true;
        } else if ( (nextMove.column-position.column == 1 
            || nextMove.column-position.column == -1)
            && nextMove.row-position.row == -1
            && position.column != nextMove.column
            && position.row != nextMove.row
            && white == false)
        {
            position = nextMove;
            if((nextMove.row == 7 && white == true)
                || (nextMove.row == 0 && white == false))
            {
                flagQueen = 1;
            }
            return true;
        } else if ( checkMaxJump(nextMove, board) )
        {
            if ( checkJumping(nextMove, board, flagQueen, pieceNum) )
            {
                position = nextMove;
                if((nextMove.row == 7 && white == true)
                    || (nextMove.row == 0 && white == false))
                {
                    flagQueen = 1;
                }
                return true;
            }
        }  
    }

    return false;
}


std::string Pawn::name()
{
    if(white)
    {
        return "b_P";
    } else
    {
        return "c_P";
    }
}