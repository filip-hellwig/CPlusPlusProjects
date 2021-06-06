#include "pawn.hpp"

bool Pawn::makeMove(Position nextMove, std::vector<std::vector<std::shared_ptr<Chessman>>>& board,
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
        if ( (nextMove.column-position.column == 1 
            || nextMove.column-position.column == -1) 
            && nextMove.row-position.row == 1
            && position.column != nextMove.column
            && position.row != nextMove.row
            && white == true)
        {
            position = nextMove;
            if((nextMove.row == 7 && white == true)
                || (nextMove.row == 0 && white == false))
            {
                flagQueen = 1;
            }
            return true;
        } else if ( (nextMove.column-position.column == 1 
            || nextMove.column-position.column == -1)
            && nextMove.row-position.row == -1
            && position.column != nextMove.column
            && position.row != nextMove.row
            && white == false)
        {
            position = nextMove;
            if((nextMove.row == 7 && white == true)
                || (nextMove.row == 0 && white == false))
            {
                flagQueen = 1;
            }
            return true;
        } else if ( checkMaxJump(nextMove, board) )
        {
            if ( makeJump(nextMove, board, flagQueen, pieceNum) )
            {
                position = nextMove;
                if((nextMove.row == 7 && white == true)
                    || (nextMove.row == 0 && white == false))
                {
                    flagQueen = 1;
                }
                return true;
            }
        }  
    }

    return false;
}

bool Pawn::checkMove(Position nextMove, std::vector<std::vector<std::shared_ptr<Chessman>>>& board)
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
        if ( (nextMove.column-position.column == 1 
            || nextMove.column-position.column == -1) 
            && nextMove.row-position.row == 1
            && position.column != nextMove.column
            && position.row != nextMove.row
            && white == true)
        {
            return true;
        } else if ( (nextMove.column-position.column == 1 
            || nextMove.column-position.column == -1)
            && nextMove.row-position.row == -1
            && position.column != nextMove.column
            && position.row != nextMove.row
            && white == false)
        {
            return true;
        } else if ( checkMaxJump(nextMove, board) )
        {
            if ( checkJump(nextMove, board) )
            {
                return true;
            }
        }  
    }

    return false;
}

int Pawn::minmaxMove(std::vector<std::vector<std::shared_ptr<Chessman>>>& board, int& currentTurnPieceNum,
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
        if ( (nextMove.column-position.column == 1 
            || nextMove.column-position.column == -1) 
            && nextMove.row-position.row == 1
            && position.column != nextMove.column
            && position.row != nextMove.row
            && white == true)
        {
            std::swap(board[nextMove.column][nextMove.row], board[position.column] [position.row]);
            histPosition = position;
            position = nextMove;

            if((nextMove.row == 7 && white == true)
                || (nextMove.row == 0 && white == false))
            {
                histPawn = board[position.column][position.row];
                board[position.column][position.row] = std::make_shared<Queen>(position.column, position.row, white);
                for(int i = 0; i < 8; i++)
                {
                    if (maxingPlayer)
                    {
                        if(currentTurnAllPieces[i]->getPosition() == position)
                        {
                            currentTurnAllPieces[i] = board[position.column][position.row];
                        }   
                    } else
                    {
                        if(opponentAllPieces[i]->getPosition() == position)
                        {
                            opponentAllPieces[i] = board[position.column][position.row];
                        }   
                    }
                    
                }
            }

            result = minmax(board, currentTurnPieceNum,
                            opponentPieceNum, currentTurnAllPieces,
                            opponentAllPieces, depth-1, maxingPlayer,
                            begin, end, nextMove);
            
            
            if((nextMove.row == 7 && white == true)
                || (nextMove.row == 0 && white == false))
            {
                board[position.column][position.row] = histPawn;
                for(int i = 0; i < 8; i++)
                {
                    if (maxingPlayer)
                    {
                        if(currentTurnAllPieces[i]->getPosition() == position)
                        {
                            currentTurnAllPieces[i] = board[position.column][position.row];
                        }   
                    } else
                    {
                        if(opponentAllPieces[i]->getPosition() == position)
                        {
                            opponentAllPieces[i] = board[position.column][position.row];
                        }   
                    }
                }
            }
            position = histPosition;
            std::swap(board[nextMove.column][nextMove.row], board[position.column] [position.row]);

            return result;

        } else if ( (nextMove.column-position.column == 1 
            || nextMove.column-position.column == -1)
            && nextMove.row-position.row == -1
            && position.column != nextMove.column
            && position.row != nextMove.row
            && white == false)
        {
            std::swap(board[nextMove.column][nextMove.row], board[position.column] [position.row]);
            histPosition = position;
            position = nextMove;

            if((nextMove.row == 7 && white == true)
                || (nextMove.row == 0 && white == false))
            {
                histPawn = board[position.column][position.row];
                board[position.column][position.row] = std::make_shared<Queen>(position.column, position.row, white);
                for(int i = 0; i < 8; i++)
                {
                    if (maxingPlayer)
                    {
                        if(currentTurnAllPieces[i]->getPosition() == position)
                        {
                            currentTurnAllPieces[i] = board[position.column][position.row];
                        }   
                    } else
                    {
                        if(opponentAllPieces[i]->getPosition() == position)
                        {
                            opponentAllPieces[i] = board[position.column][position.row];
                        }   
                    }
                    
                }
            }

            result = minmax(board, currentTurnPieceNum,
                            opponentPieceNum, currentTurnAllPieces,
                            opponentAllPieces, depth-1, maxingPlayer,
                            begin, end, nextMove);
            
            
            if((nextMove.row == 7 && white == true)
                || (nextMove.row == 0 && white == false))
            {
                board[position.column][position.row] = histPawn;
                for(int i = 0; i < 8; i++)
                {
                    if (maxingPlayer)
                    {
                        if(currentTurnAllPieces[i]->getPosition() == position)
                        {
                            currentTurnAllPieces[i] = board[position.column][position.row];
                        }   
                    } else
                    {
                        if(opponentAllPieces[i]->getPosition() == position)
                        {
                            opponentAllPieces[i] = board[position.column][position.row];
                        }   
                    }
                }
            }
            position = histPosition;
            std::swap(board[nextMove.column][nextMove.row], board[position.column] [position.row]);

            return result;
        } else if ( checkMaxJump(nextMove, board) )
        {
            if(maxingPlayer) { histNum = opponentPieceNum; }
            else { histNum = currentTurnPieceNum; }

            if ( minmaxJump(board, currentTurnPieceNum,
                            opponentPieceNum, currentTurnAllPieces,
                            opponentAllPieces, depth, maxingPlayer,
                            begin, end, nextMove, flagQueen) )
            {
                std::swap(board[nextMove.column][nextMove.row], board[position.column] [position.row]);
                histPosition = position;
                position = nextMove;

                if((nextMove.row == 7 && white == true)
                    || (nextMove.row == 0 && white == false))
                {
                    histPawn = board[position.column][position.row];
                    board[position.column][position.row] = std::make_shared<Queen>(position.column, position.row, white);
                    for(int i = 0; i < 8; i++)
                    {
                        if (maxingPlayer)
                        {
                            if(currentTurnAllPieces[i]->getPosition() == position)
                            {
                                currentTurnAllPieces[i] = board[position.column][position.row];
                            }   
                        } else
                        {
                            if(opponentAllPieces[i]->getPosition() == position)
                            {
                                opponentAllPieces[i] = board[position.column][position.row];
                            }   
                        }
                        
                    }
                }

                result = minmax(board, currentTurnPieceNum,
                                opponentPieceNum, currentTurnAllPieces,
                                opponentAllPieces, depth-1, maxingPlayer,
                                begin, end, nextMove);
                
                
                if((nextMove.row == 7 && white == true)
                    || (nextMove.row == 0 && white == false))
                {
                    board[position.column][position.row] = histPawn;
                    for(int i = 0; i < 8; i++)
                    {
                        if (maxingPlayer)
                        {
                            if(currentTurnAllPieces[i]->getPosition() == position)
                            {
                                currentTurnAllPieces[i] = board[position.column][position.row];
                            }   
                        } else
                        {
                            if(opponentAllPieces[i]->getPosition() == position)
                            {
                                opponentAllPieces[i] = board[position.column][position.row];
                            }   
                        }
                    }
                }
                position = histPosition;
                std::swap(board[nextMove.column][nextMove.row], board[position.column] [position.row]);

                if(maxingPlayer) { opponentPieceNum = histNum; }
                else { currentTurnPieceNum = histNum; }

                return result;
            }
        }
    }

    return result;
}


bool Pawn::isQueen()
{
    return false;
}