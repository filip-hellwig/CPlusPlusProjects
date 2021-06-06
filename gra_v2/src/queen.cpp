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
        
        if ( checkMaxJump(nextMove, board) )
        {
            if ( makeJump(nextMove, board, flagQueen, pieceNum))
            {
                position = nextMove;
                return true;
            } 
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
        
        if ( checkMaxJump(nextMove, board) )
        {
            if ( checkJump(nextMove, board))
            {
                return true;
            }
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

int Queen::minmaxMove(std::vector<std::vector<std::shared_ptr<Chessman>>>& board, int& currentTurnPieceNum,
                        int& opponentPieceNum, std::vector<std::shared_ptr<Chessman>>& currentTurnAllPieces,
                        std::vector<std::shared_ptr<Chessman>>& opponentAllPieces, int depth, bool maxingPlayer,
                        Position& begin, Position& end, Position nextMove)
{
    int result = -1;
    std::shared_ptr<Chessman> histPawn;
    Position histPosition;
    int flagQueen = 0, histNum;
    
    if ( board[nextMove.column][nextMove.row] != nullptr )
    {  
        if (nextMove != position)
        {
            return result;
        }
        
    }

    if (checkIndexValidity(nextMove.column, nextMove.row))
    {
        if ( checkMaxJump(nextMove, board) )
        {
            if(maxingPlayer) { histNum = opponentPieceNum; }
            else { histNum = currentTurnPieceNum; }

            if ( minmaxJump(board, currentTurnPieceNum,
                            opponentPieceNum, currentTurnAllPieces,
                            opponentAllPieces, depth, maxingPlayer,
                            begin, nextMove, nextMove, flagQueen) )
            {
                std::swap(board[nextMove.column][nextMove.row], board[position.column] [position.row]);
                histPosition = position;
                position = nextMove;

                result = minmax(board, currentTurnPieceNum,
                                opponentPieceNum, currentTurnAllPieces,
                                opponentAllPieces, depth-1, maxingPlayer,
                                begin, end, nextMove);
                
                position = histPosition;
                std::swap(board[nextMove.column][nextMove.row], board[position.column] [position.row]);

                if(maxingPlayer) { opponentPieceNum = histNum; }
                else { currentTurnPieceNum = histNum; }

                return result;
            }
        }
        
        if ( abs(position.column-nextMove.column) == abs(position.row-nextMove.row))
        {
            if (nextMove.column-position.column > 0 && nextMove.row-position.row > 0)
            {
                for (int i = 1; i < abs(nextMove.row - position.row); i++)
                {
                    if(board[position.column+i][position.row+i] != nullptr)
                    {
                        return result;
                    }
                }
            } else if (nextMove.column-position.column > 0 && nextMove.row-position.row < 0)
            {
                for (int i = 1; i < abs(nextMove.row - position.row); i++)
                {
                    if(board[position.column+i][position.row-i] != nullptr)
                    {
                        return result;
                    }
                }
            } else if (nextMove.column-position.column < 0 && nextMove.row-position.row > 0)
            {
                for (int i = 1; i < abs(nextMove.row - position.row); i++)
                {
                    if(board[position.column-i][position.row+i] != nullptr)
                    {
                        return result;
                    }
                }
            } else
            {
                for (int i = 1; i < abs(nextMove.row - position.row); i++)
                {
                    if(board[position.column-i][position.row-i] != nullptr)
                    {
                        return result;
                    }
                }
            }
            if (position.column != nextMove.column 
                || position.row != nextMove.row)
            {
                std::swap(board[nextMove.column][nextMove.row], board[position.column] [position.row]);
                histPosition = position;
                position = nextMove;

                result = minmax(board, currentTurnPieceNum,
                                opponentPieceNum, currentTurnAllPieces,
                                opponentAllPieces, depth-1, maxingPlayer,
                                begin, end, nextMove);
                
                
                position = histPosition;
                std::swap(board[nextMove.column][nextMove.row], board[position.column] [position.row]);

                return result;
            }
        }
    }

    return result;
}


bool Queen::isQueen()
{
    return true;
}