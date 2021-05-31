#include "queen.hpp"

bool Queen::makeMove(Position nextMove, std::vector<std::vector<std::shared_ptr<Chessman>>>& board,
                        int& flagQueen, int& pieceNum)
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
        if ( makeJump(nextMove, board, flagQueen, pieceNum))
        {
            position = nextMove;
            return true;
        }  
        
        if ( abs(position.column-nextMove.column) == abs(position.row-nextMove.row))
        {
            if (nextMove.column-position.column > 0 && nextMove.row-position.row > 0)
            {
                for (int i = 1; i < abs(nextMove.row - position.row); i++)
                {
                    if(board[position.column+i][position.row+i] != nullptr)
                    {
                        return false;
                    }
                }
            } else if (nextMove.column-position.column > 0 && nextMove.row-position.row < 0)
            {
                for (int i = 1; i < abs(nextMove.row - position.row); i++)
                {
                    if(board[position.column+i][position.row-i] != nullptr)
                    {
                        return false;
                    }
                }
            } else if (nextMove.column-position.column < 0 && nextMove.row-position.row > 0)
            {
                for (int i = 1; i < abs(nextMove.row - position.row); i++)
                {
                    if(board[position.column-i][position.row+i] != nullptr)
                    {
                        return false;
                    }
                }
            } else
            {
                for (int i = 1; i < abs(nextMove.row - position.row); i++)
                {
                    if(board[position.column-i][position.row-i] != nullptr)
                    {
                        return false;
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


bool Queen::checkMove(Position nextMove, std::vector<std::vector<std::shared_ptr<Chessman>>>& board)
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
        if ( checkJump(nextMove, board))
        {
            return true;
        } 


        if ( abs(position.column-nextMove.column) == abs(position.row-nextMove.row))
        {
            if (nextMove.column-position.column > 0 && nextMove.row-position.row > 0)
            {
                for (int i = 1; i < abs(nextMove.row - position.row); i++)
                {
                    if(board[position.column+i][position.row+i] != nullptr)
                    {
                        return false;
                    }
                }
            } else if (nextMove.column-position.column > 0 && nextMove.row-position.row < 0)
            {
                for (int i = 1; i < abs(nextMove.row - position.row); i++)
                {
                    if(board[position.column+i][position.row-i] != nullptr)
                    {
                        return false;
                    }
                }
            } else if (nextMove.column-position.column < 0 && nextMove.row-position.row > 0)
            {
                for (int i = 1; i < abs(nextMove.row - position.row); i++)
                {
                    if(board[position.column-i][position.row+i] != nullptr)
                    {
                        return false;
                    }
                }
            } else
            {
                for (int i = 1; i < abs(nextMove.row - position.row); i++)
                {
                    if(board[position.column-i][position.row-i] != nullptr)
                    {
                        return false;
                    }
                }
            }
            if (position.column != nextMove.column 
                || position.row != nextMove.row)
            {
                return true;
            }
        }
    }

    return false;
}


bool Queen::isQueen()
{
    return true;
}