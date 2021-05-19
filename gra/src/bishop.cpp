#include "bishop.hpp"

bool Bishop::makeMove(char column, int row)
{
    Position nextMove;

    nextMove = translateMove(column, row);

    if (checkIndexValidity(nextMove.column, nextMove.row))
    {
        if ( abs(position.column-nextMove.column) == abs(position.row-nextMove.row))
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