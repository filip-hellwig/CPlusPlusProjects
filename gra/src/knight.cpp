#include "knight.hpp"

bool Knight::makeMove(char column, int row)
{
    Position nextMove;

    nextMove = translateMove(column, row);

    if (checkIndexValidity(nextMove.column, nextMove.row))
    {
        if ( abs(position.column-nextMove.column) == 2 && abs(position.row-nextMove.row) == 1
            || abs(position.column-nextMove.column) == 1 && abs(position.row-nextMove.row) == 2)
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