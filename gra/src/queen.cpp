#include "queen.hpp"

bool Queen::makeMove(int column, int row, std::vector<std::vector<std::shared_ptr<Chessman>>> board)
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

std::string Queen::name()
{
    if(white)
    {
        return "b_Q";
    } else
    {
        return "c_Q";
    }
}