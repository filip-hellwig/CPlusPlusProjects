#include "rook.hpp"

bool Rook::makeMove(char column, int row)
{
    Position nextMove;

    nextMove = translateMove(column, row);

    if (checkIndexValidity(nextMove.column, nextMove.row))
    {
        if ( nextMove.column == position.column
            || nextMove.row == position.row )
        {
            if (position.column != nextMove.column 
                || position.row != nextMove.row)
            {
                position = nextMove;
                return true;
            }
        }
    }

    return false;
}