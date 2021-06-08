#include "pawn.hpp"

bool Pawn::makeMove(Position nextMove, std::vector<std::vector<std::shared_ptr<Chessman>>>& board,
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
        /* Sprawdzamy zwykły ruch dla białych pionków */
        if ( (nextMove.column-position.column == 1 
            || nextMove.column-position.column == -1) 
            && nextMove.row-position.row == 1
            && position.column != nextMove.column
            && position.row != nextMove.row
            && white)
        {
            /* Zmieniamy pozycję pionka */
            position = nextMove;

            /* Sprawdzamy czy staje się królową */
            if((nextMove.row == 7 && white)
                || (nextMove.row == 0 && !white))
            {
                flagQueen = true;
            }

            return true;
        }

        /* Sprawdzamy zwykły ruch dla czarnych pionków */
        else if ( (nextMove.column-position.column == 1 
            || nextMove.column-position.column == -1)
            && nextMove.row-position.row == -1
            && position.column != nextMove.column
            && position.row != nextMove.row
            && !white)
        {
            /* Zmieniamy pozycję pionka */
            position = nextMove;

            /* Sprawdzamy czy staje się królową */
            if((nextMove.row == 7 && white)
                || (nextMove.row == 0 && !white))
            {
                flagQueen = true;
            }
            
            return true;
        } 
        
        /* Sprawdzamy bicie */
        else if ( checkMaxJump(nextMove, board) )
        {
            if ( makeJump(nextMove, board, flagQueen, pieceNum) )
            {
                /* Zmieniamy pozycję pionka */
                position = nextMove;

                /* Sprawdzamy czy staje się królową */
                if((nextMove.row == 7 && white)
                    || (nextMove.row == 0 && !white))
                {
                    flagQueen = true;
                }
                
                return true;
            }
        }  
    }

    return false;
}

bool Pawn::checkMove(Position nextMove, std::vector<std::vector<std::shared_ptr<Chessman>>>& board)
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
        /* Sprawdzamy zwykły ruch dla białych pionków */
        if ( (nextMove.column-position.column == 1 
            || nextMove.column-position.column == -1) 
            && nextMove.row-position.row == 1
            && position.column != nextMove.column
            && position.row != nextMove.row
            && white)
        {
            return true;
        }
        
        /* Sprawdzamy zwykły ruch dla czarnych pionków */
        else if ( (nextMove.column-position.column == 1 
            || nextMove.column-position.column == -1)
            && nextMove.row-position.row == -1
            && position.column != nextMove.column
            && position.row != nextMove.row
            && !white)
        {
            return true;
        } 
        
        /* Sprawdzamy bicie */
        else if ( checkMaxJump(nextMove, board) )
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

    
    if (checkIndexValidity(nextMove.column, nextMove.row))
    {
        /* Sprawdzamy zwykły ruch dla białych pionków */
        if ( (nextMove.column-position.column == 1 
            || nextMove.column-position.column == -1) 
            && nextMove.row-position.row == 1
            && position.column != nextMove.column
            && position.row != nextMove.row
            && white)
        {
            return partMinmaxMove(board, currentTurnPieceNum,
                                opponentPieceNum, currentTurnAllPieces,
                                opponentAllPieces, depth, maxingPlayer,
                                begin, end, nextMove);

        } 
        
        /* Sprawdzamy zwykły ruch dla czarnych pionków */
        else if ( (nextMove.column-position.column == 1 
            || nextMove.column-position.column == -1)
            && nextMove.row-position.row == -1
            && position.column != nextMove.column
            && position.row != nextMove.row
            && !white)
        {
            return partMinmaxMove(board, currentTurnPieceNum,
                                opponentPieceNum, currentTurnAllPieces,
                                opponentAllPieces, depth, maxingPlayer,
                                begin, end, nextMove);
        } 
        
        /* Sprawdzamy bicie */
        else if ( checkMaxJump(nextMove, board) )
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
    }

    return result;
}


int Pawn::partMinmaxMove(std::vector<std::vector<std::shared_ptr<Chessman>>>& board, int& currentTurnPieceNum,
                                int& opponentPieceNum, std::vector<std::shared_ptr<Chessman>>& currentTurnAllPieces,
                                std::vector<std::shared_ptr<Chessman>>& opponentAllPieces, int depth, bool maxingPlayer,                        
                                Position& begin, Position& end, Position nextMove)
{
    std::shared_ptr<Chessman> histPawn;
    Position histPosition;
    int result = -1;

    /* Zmieniamy pozycję pionka */
    std::swap(board[nextMove.column][nextMove.row], board[position.column] [position.row]);
    histPosition = position;
    position = nextMove;

    /* Zamiana pionka na królową */
    if((nextMove.row == 7 && white)
        || (nextMove.row == 0 && !white))
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
                    opponentAllPieces, depth-1, !maxingPlayer,
                    begin, end, nextMove);
    
    
    /* Cofnięcie zmiany pionka na królową */
    if((nextMove.row == 7 && white)
        || (nextMove.row == 0 && !white))
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

    /* Przypisanie starej pozycji pionkowi */
    position = histPosition;
    std::swap(board[nextMove.column][nextMove.row], board[position.column] [position.row]);

    return result;
}


bool Pawn::isQueen()
{
    return false;
}