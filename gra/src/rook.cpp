#include "rook.hpp"

bool Rook::makeMove(int column, int row, std::vector<std::vector<std::shared_ptr<Chessman>>> board)
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
        if ( nextMove.column == position.column
            || nextMove.row == position.row )
        {   
            if (nextMove.column == position.column)
            {
                if(nextMove.row - position.row > 0)
                {
                    for (int i = 1; i < abs(nextMove.row - position.row)-1; i++)
                    {
                        if(board[position.column][position.row+i] != nullptr)
                        {
                            return false;
                        }
                    }
                } else
                {
                    for (int i = 1; i < abs(nextMove.column - position.column)-1; i++)
                    {
                        if(board[position.column][position.row-i] != nullptr)
                        {
                            return false;
                        }
                    }
                }
            } else
            {
                if(nextMove.column - position.column > 0)
                {
                    for (int i = 1; i < abs(nextMove.column - position.column)-1; i++)
                    {
                        if(board[position.column+i][position.row] != nullptr)
                        {
                            return false;
                        }
                    }
                } else
                {
                    for (int i = 1; i < abs(nextMove.column - position.column)-1; i++)
                    {
                        if(board[position.column-i][position.row] != nullptr)
                        {
                            return false;
                        }
                    }
                }
            }

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

std::string Rook::name()
{
    if(white)
    {
        return "b_R";
    } else
    {
        return "c_R";
    }
}