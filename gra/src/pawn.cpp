#include "pawn.hpp"

bool Pawn::makeMove(char column, int row)
{
    Position nextMove;

    nextMove = translateMove(column, row);

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