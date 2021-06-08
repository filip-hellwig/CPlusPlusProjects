#include "queen.hpp"

bool Queen::makeMove(Position nextMove, std::vector<std::vector<std::shared_ptr<Chessman>>>& board,
                        bool& flagQueen, int& pieceNum)
{
    /* Sprawdzamy czy na tym polu coś stoi */
    if ( board[nextMove.column][nextMove.row] != nullptr )
    {  
        if (nextMove != position)
        {
            return false;
        }
        
    }

    if (checkIndexValidity(nextMove.column, nextMove.row))
    {
        /* Sprawdzamy bicie*/
        if ( checkMaxJump(nextMove, board) )
        {
            if ( makeJump(nextMove, board, flagQueen, pieceNum))
            {
                position = nextMove;
                return true;
            } 
        } 
        
        /* Sprawdzamy zwykły ruch */
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

            /* Jeżeli miejsce różni się obecnego to zmieniamy pozycję */
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
    /* Sprawdzamy czy na tym polu coś stoi */
    if ( board[nextMove.column][nextMove.row] != nullptr )
    {  
        if (nextMove != position)
        {
            return false;
        }
        
    }

    if (checkIndexValidity(nextMove.column, nextMove.row))
    {
        /* Sprawdzamy bicie */   
        if ( checkMaxJump(nextMove, board) )
        {
            if ( checkJump(nextMove, board))
            {
                return true;
            }
        } 

        /* Sprawdzamy zwykły ruch */ 
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
    std::vector<std::vector<std::shared_ptr<Chessman>>> histBoard;
    bool flagQueen = false;
    int histNum;
    
    /* Sprawdzamy czy na tym polu coś stoi */
    if ( board[nextMove.column][nextMove.row] != nullptr )
    {  
        if (nextMove != position)
        {
            return result;
        }
    }

    /* Sprawdzamy bicie */
    if (checkIndexValidity(nextMove.column, nextMove.row))
    {
        if ( checkMaxJump(nextMove, board) )
        {
            bool isPossible = false;

            /* Zapamiętujemy zmienne oraz wykonujemy skok */
            histBoard = board;
            if(maxingPlayer) 
            {
                histNum = opponentPieceNum;
                isPossible = makeJump(nextMove, board, flagQueen, opponentPieceNum); 
            } else 
            {
                histNum = currentTurnPieceNum;
                isPossible = makeJump(nextMove, board, flagQueen, currentTurnPieceNum); 
            }

            /* Jeżeli skok był możliwy to wykonujemy dalszą część */
            if ( isPossible )
            {
                result = partMinmaxMove(board, currentTurnPieceNum,
                                opponentPieceNum, currentTurnAllPieces,
                                opponentAllPieces, depth, maxingPlayer,
                                begin, end, nextMove);

                /* Cofamy działania skoku, przywracamy figury na planszę */
                if(maxingPlayer) { opponentPieceNum = histNum; }
                else { currentTurnPieceNum = histNum; }
                board = histBoard;

                for (int i = 0; i < 8; i++)
                {
                    for (int j = 0; j < 8; j++) {
                        if(board[j][i] != nullptr)
                        {
                            if(!board[j][i]->getExistance()) { board[j][i]->changeExistance(true); }
                        }
                    }
                }

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
                return partMinmaxMove(board, currentTurnPieceNum,
                                opponentPieceNum, currentTurnAllPieces,
                                opponentAllPieces, depth, maxingPlayer,
                                begin, end, nextMove);
            }
        }
    }

    return result;
}

int Queen::partMinmaxMove(std::vector<std::vector<std::shared_ptr<Chessman>>>& board, int& currentTurnPieceNum,
                                int& opponentPieceNum, std::vector<std::shared_ptr<Chessman>>& currentTurnAllPieces,
                                std::vector<std::shared_ptr<Chessman>>& opponentAllPieces, int depth, bool maxingPlayer,                        
                                Position& begin, Position& end, Position nextMove)
{
    std::shared_ptr<Chessman> histPawn;
    Position histPosition;
    int result = -1;

    /* Zmieniamy pozycję królowej */
    std::swap(board[nextMove.column][nextMove.row], board[position.column] [position.row]);
    histPosition = position;
    position = nextMove;

    result = minmax(board, currentTurnPieceNum,
                    opponentPieceNum, currentTurnAllPieces,
                    opponentAllPieces, depth-1, !maxingPlayer,
                    begin, end, nextMove);
    
    
    /* Przypisanie starej pozycji królowej */
    position = histPosition;
    std::swap(board[nextMove.column][nextMove.row], board[position.column] [position.row]);

    return result;
}


bool Queen::isQueen()
{
    return true;
}