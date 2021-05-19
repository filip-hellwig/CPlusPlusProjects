#include "queen.hpp"

bool Queen::makeMove(char column, int row)
{
    Position nextMove;

    nextMove = translateMove(column, row);

    if (checkIndexValidity(nextMove.column, nextMove.row))
    {
        if ( abs(position.column-nextMove.column) <= 1 
            && abs(position.row-nextMove.row) <= 1)
        {
            if (position.column != nextMove.column 
                || position.row != nextMove.row)
            {
                position = nextMove;
                return true;
            }
        } else if ( nextMove.column == position.column
            || nextMove.row == position.row )
        {
            if (position.column != nextMove.column 
                || position.row != nextMove.row)
            {
                position = nextMove;
                return true;
            }
        } else if ( abs(position.column-nextMove.column) == abs(position.row-nextMove.row))
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