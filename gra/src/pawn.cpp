#include "pawn.hpp"

bool Pawn::makeMove(int column, int row, std::vector<std::vector<std::shared_ptr<Chessman>>> board)
{
    Position nextMove(column, row);

    if ( board[nextMove.row][nextMove.column] != nullptr )
    {
        if ( board[nextMove.row][nextMove.column]->getWhite() == white)
        {
            return false;
        }
    }

    if (checkIndexValidity(nextMove.column, nextMove.row))
    {
        if (white)
        {
            if (position.row == 1)
            {
                if ( position.column == nextMove.column 
                    && (nextMove.row-position.row == 1
                    || nextMove.row-position.row == 2))
                {
                    if (position.column != nextMove.column 
                        || position.row != nextMove.row)
                    {
                        position = nextMove;
                        return true;
                    }
                }
            } else
            {
                if ( position.column == nextMove.column 
                    && nextMove.row-position.row == 1)
                {
                    if (position.column != nextMove.column 
                        || position.row != nextMove.row)
                    {
                        position = nextMove;
                        return true;
                    }
                }
            }
        } else
        {
            if (position.row == 6)
            {
                if ( position.column == nextMove.column 
                    && (nextMove.row - position.row == -1
                    || nextMove.row - position.row == -2))
                {
                    if (position.column != nextMove.column 
                        || position.row != nextMove.row)
                    {
                        position = nextMove;
                        return true;
                    }
                }
            } else
            {
                if ( position.column == nextMove.column 
                    && nextMove.row-position.row == -1)
                {
                    if (position.column != nextMove.column 
                        || position.row != nextMove.row)
                    {
                        position = nextMove;
                        return true;
                    }
                }
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