#ifndef CHESSMAN_HPP_
#define CHESSMAN_HPP_

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <memory>
#include "position.hpp"

#define INFI 20000


class Player;

class Chessman
{
    protected:
        Position position; 
        bool existance;
        bool white;
        bool queen;
    
    public:
        virtual bool makeMove(Position nextMove, std::vector<std::vector<std::shared_ptr<Chessman>>>& board,
                                int& flagQueen, int& pieceNum ) = 0;
        virtual bool checkMove(Position nextMove, std::vector<std::vector<std::shared_ptr<Chessman>>>& board) = 0;
        virtual int minmaxMove(std::vector<std::vector<std::shared_ptr<Chessman>>>& board, int& currentTurnPieceNum,
                                int& opponentPieceNum, std::vector<std::shared_ptr<Chessman>>& currentTurnAllPieces,
                                std::vector<std::shared_ptr<Chessman>>& opponentAllPieces, int depth, bool maxingPlayer,
                                Position& begin, Position& end, Position nextMove) = 0;                           
        virtual bool isQueen() = 0;


        Chessman(int column, int row, bool isWhite)
        {
            Position newPosition(column, row);
            position = newPosition;
            existance = true;
            white = isWhite;
        }        

        bool checkIndexValidity(int column, int row)
        {
            if (row > 7 || row < 0)
            {
                return false;
            }
            if (column > 7 || column < 0)
            {
                return false;
            }
            return true;
        }

        bool getWhite() { return white; }
        bool getExistance() { return existance; }
        void changeExistance(bool b)
        {
            existance = b;
        }
        void changePosition(Position pos)
        {
            position = pos;
        }
        Position getPosition()
        {
            return position;
        }



        bool checkMaxJumpShort(int column, int row, int column2, int row2,
                                std::vector<std::vector<std::shared_ptr<Chessman>>>& board)
        {
            Position pos;

            if (checkIndexValidity(column2, row2))
            {
                if(board[column][row] != nullptr
                    && board[column][row]->getWhite() != white
                    && (board[column2][row2] == nullptr
                    || (board[column2][row2] != nullptr
                    && pos.setPostition(column2, row2) == position)))
                { return true; }
            }

            return false;
        }

        bool checkMaxJump(Position nextMove, std::vector<std::vector<std::shared_ptr<Chessman>>>& board)
        {
            int i = 0;
            Position pos;

            if (checkMaxJumpShort(nextMove.column+1, nextMove.row+1, nextMove.column+2, nextMove.row+2, board))
            { i++; }
            if (checkMaxJumpShort(nextMove.column-1, nextMove.row+1, nextMove.column-2, nextMove.row+2, board))
            { i++; }
            if (checkMaxJumpShort(nextMove.column+1, nextMove.row-1, nextMove.column+2, nextMove.row-2, board))
            { i++; }
            if (checkMaxJumpShort(nextMove.column-1, nextMove.row-1, nextMove.column-2, nextMove.row-2, board))
            { i++; }

            if (i > 1) { return false; }
            else { return true; } 
        }




        bool makeJumpShort(int column, int row, int column2, int row2,
                                std::vector<std::vector<std::shared_ptr<Chessman>>>& board,
                                int& flagQueen, int& pieceNum)
        {
            Position newPosition;
            std::shared_ptr<Chessman> histPiece;

            if (checkIndexValidity(column2, row2))
            {
                if(board[column][row] != nullptr
                && board[column][row]->getWhite() != white)
                {
                    if (board[column2][row2] != nullptr)
                    {
                        if (newPosition.setPostition(column2, row2) == position)
                        {
                            board[column][row]->changeExistance(false);
                            board[column][row] = nullptr;
                            pieceNum += -1;
                            return true;
                        }
                    } else 
                    {
                        board[column][row]->changeExistance(false);
                        histPiece = board[column][row];
                        board[column][row] = nullptr;
                        pieceNum += -1;
                        
                        if(makeJump(newPosition.setPostition(column2, row2), board, flagQueen, pieceNum))
                        {
                            if((row2 == 7 && white)
                                || (row2 == 0 && !white))
                            {
                                flagQueen = 1;
                            }
                            return true;
                        }

                        board[column][row] = histPiece;
                        board[column][row]->changeExistance(true);
                        histPiece = nullptr;
                        pieceNum += 1;
                    }
                }
            }
            return false;
        }

        bool makeJump(Position nextMove, std::vector<std::vector<std::shared_ptr<Chessman>>>& board,
                            int& flagQueen, int& pieceNum)
        {
            if(makeJumpShort(nextMove.column+1, nextMove.row+1, nextMove.column+2, nextMove.row+2,
                                    board, flagQueen, pieceNum))
            { return true; }
            if(makeJumpShort(nextMove.column-1, nextMove.row+1, nextMove.column-2, nextMove.row+2,
                                    board, flagQueen, pieceNum))
            { return true; }
            if(makeJumpShort(nextMove.column+1, nextMove.row-1, nextMove.column+2, nextMove.row-2,
                                    board, flagQueen, pieceNum))
            { return true; }
            if(makeJumpShort(nextMove.column-1, nextMove.row-1, nextMove.column-2, nextMove.row-2,
                                    board, flagQueen, pieceNum))
            { return true; }
            return false;
        }



        bool checkJumpShort(int column, int row, int column2, int row2,
                                std::vector<std::vector<std::shared_ptr<Chessman>>>& board)
        {
            Position newPosition;
            std::shared_ptr<Chessman> histPiece;

            if (checkIndexValidity(column2, row2)
                && board[column][row] != nullptr
                && board[column][row]->getWhite() != white)
            {
                if (board[column2][row2] != nullptr)
                {
                    if (newPosition.setPostition(column2, row2) == position)
                    {
                        return true;
                    }
                } else 
                {
                    board[column][row]->changeExistance(false);
                    histPiece = board[column][row];
                    board[column][row] = nullptr;
                    
                    if(checkJump(newPosition.setPostition(column2, row2), board))
                    {
                        board[column][row] = histPiece;
                        board[column][row]->changeExistance(true);
                        histPiece = nullptr;

                        return true;
                    }

                    board[column][row] = histPiece;
                    board[column][row]->changeExistance(true);
                    histPiece = nullptr;
                }
            }
            return false;
        }

        bool checkJump(Position nextMove, std::vector<std::vector<std::shared_ptr<Chessman>>>& board)
        {
            if(checkJumpShort(nextMove.column+1, nextMove.row+1, nextMove.column+2, nextMove.row+2,
                                    board))
            { return true; }
            if(checkJumpShort(nextMove.column-1, nextMove.row+1, nextMove.column-2, nextMove.row+2,
                                    board))
            { return true; }
            if(checkJumpShort(nextMove.column+1, nextMove.row-1, nextMove.column+2, nextMove.row-2,
                                    board))
            { return true; }
            if(checkJumpShort(nextMove.column-1, nextMove.row-1, nextMove.column-2, nextMove.row-2,
                                    board))
            { return true; }
            return false;
        }


        bool minmaxJumpShort(int column, int row, int column2, int row2,
                                std::vector<std::vector<std::shared_ptr<Chessman>>>& board,
                                int& currentTurnPieceNum, int& opponentPieceNum,
                                std::vector<std::shared_ptr<Chessman>>& currentTurnAllPieces,
                                std::vector<std::shared_ptr<Chessman>>& opponentAllPieces,
                                int depth, bool maxingPlayer,
                                Position& begin, Position& end, Position nextMove, int& flagQueen)
        {
            Position newPosition;
            std::shared_ptr<Chessman> histPiece;

            if (checkIndexValidity(column2, row2))
            {
                if(board[column][row] != nullptr
                && board[column][row]->getWhite() != white)
                {
                    if (board[column2][row2] != nullptr)
                    {
                        if (newPosition.setPostition(column2, row2) == position)
                        {
                            if(maxingPlayer) {opponentPieceNum += -1;}
                            else {currentTurnPieceNum += -1;}
                            return true;
                        }
                    } else 
                    {
                        board[column][row]->changeExistance(false);
                        histPiece = board[column][row];
                        board[column][row] = nullptr;
                        if(maxingPlayer) {opponentPieceNum += -1;}
                        else {currentTurnPieceNum += -1;}
                        
                        if(minmaxJump(board, currentTurnPieceNum,
                                        opponentPieceNum, currentTurnAllPieces,
                                        opponentAllPieces, depth, maxingPlayer,
                                        begin, end, newPosition.setPostition(column2, row2), flagQueen))
                        {
                            if((row2 == 7 && white)
                                || (row2 == 0 && !white))
                            {
                                flagQueen = 1;
                            }

                            board[column][row] = histPiece;
                            board[column][row]->changeExistance(true);
                            histPiece = nullptr;
                            
                            return true;
                        }

                        board[column][row] = histPiece;
                        board[column][row]->changeExistance(true);
                        histPiece = nullptr;
                        if(maxingPlayer) {opponentPieceNum += 1;}
                        else {currentTurnPieceNum += 1;}
                    }
                }
            }
            return false;
        }

        bool minmaxJump(std::vector<std::vector<std::shared_ptr<Chessman>>>& board, int& currentTurnPieceNum,
                    int& opponentPieceNum, std::vector<std::shared_ptr<Chessman>>& currentTurnAllPieces,
                    std::vector<std::shared_ptr<Chessman>>& opponentAllPieces, int depth, bool maxingPlayer,
                    Position& begin, Position& end, Position nextMove, int& flagQueen)
        {
            if(minmaxJumpShort(nextMove.column+1, nextMove.row+1, nextMove.column+2, nextMove.row+2,
                                board, currentTurnPieceNum,
                                opponentPieceNum, currentTurnAllPieces,
                                opponentAllPieces, depth, maxingPlayer,
                                begin, end, nextMove, flagQueen))
            { return true; }
            if(minmaxJumpShort(nextMove.column-1, nextMove.row+1, nextMove.column-2, nextMove.row+2,
                                board, currentTurnPieceNum,
                                opponentPieceNum, currentTurnAllPieces,
                                opponentAllPieces, depth, maxingPlayer,
                                begin, end, nextMove, flagQueen))
            { return true; }
            if(minmaxJumpShort(nextMove.column+1, nextMove.row-1, nextMove.column+2, nextMove.row-2,
                                board, currentTurnPieceNum,
                                opponentPieceNum, currentTurnAllPieces,
                                opponentAllPieces, depth, maxingPlayer,
                                begin, end, nextMove, flagQueen))
            { return true; }
            if(minmaxJumpShort(nextMove.column-1, nextMove.row-1, nextMove.column-2, nextMove.row-2,
                                board, currentTurnPieceNum,
                                opponentPieceNum, currentTurnAllPieces,
                                opponentAllPieces, depth, maxingPlayer,
                                begin, end, nextMove, flagQueen))
            { return true; }
            return false;
        }


        int minmax(std::vector<std::vector<std::shared_ptr<Chessman>>>& board, int& currentTurnPieceNum,
                    int& opponentPieceNum, std::vector<std::shared_ptr<Chessman>>& currentTurnAllPieces,
                    std::vector<std::shared_ptr<Chessman>>& opponentAllPieces, int depth, bool maxingPlayer,
                    Position& begin, Position& end, Position nextMove) 
        {
            if ((depth == 0
                || opponentPieceNum == 0)
                && !maxingPlayer)
            { return 8-opponentPieceNum; }
            if ((depth == 0 
                || currentTurnPieceNum == 0)
                && maxingPlayer)
            { return opponentPieceNum; }
            
            bool noMoveFlag = true;
            std::vector<Position> vec = begin.allPostitons();
            if(maxingPlayer)
            {
                for(int i = 0; i < 8; i++)
                {
                    if (opponentAllPieces[i]->getExistance())
                    {
                        for (int j = 0; j < 32; j++)
                        {
                            if (opponentAllPieces[i]->checkMove(vec[j], board))
                            {
                                noMoveFlag = false;
                            }
                        }
                        
                    }
                }
                if(noMoveFlag) { return -10; }
            } else
            {
                for(int i = 0; i < 8; i++)
                {
                    if (currentTurnAllPieces[i]->getExistance())
                    {
                        for (int j = 0; j < 32; j++)
                        {
                            if (!currentTurnAllPieces[i]->checkMove(vec[j], board))
                            {
                                noMoveFlag = false;
                            }
                        }
                        
                    }
                }
                if(noMoveFlag) { return 10; }
            }
            

            if (maxingPlayer)
            {
                int minEval = INFI;
                int eval = INFI;

                for(int i = 0; i < 8; i++)
                {
                    if (currentTurnAllPieces[i]->getExistance())
                    {
                        for (int j = 0; j < 32; j++)
                        {
                            eval = currentTurnAllPieces[i]->minmaxMove(board, currentTurnPieceNum,
                                                                    opponentPieceNum, currentTurnAllPieces,
                                                                    opponentAllPieces, depth, maxingPlayer,
                                                                    begin, end, vec[j]);
                            {
                                if (eval < minEval && eval != -1)
                                {
                                    minEval = eval;
                                    begin = currentTurnAllPieces[i]->getPosition();
                                    end = vec[j];
                                }
                            }
                        }
                        
                    }
                }

                return minEval;
            } else
            {
                int maxEval = -INFI;
                int eval = -INFI;

                for(int i = 0; i < 8; i++)
                {
                    if (opponentAllPieces[i]->getExistance())
                    {
                        for (int j = 0; j < 32; j++)
                        {
                            eval = opponentAllPieces[i]->minmaxMove(board, currentTurnPieceNum,
                                                                    opponentPieceNum, currentTurnAllPieces,
                                                                    opponentAllPieces, depth, maxingPlayer,
                                                                    begin, end, vec[j]);
                            {
                                if (eval > maxEval && eval != -1)
                                {
                                    maxEval = eval;
                                    begin = currentTurnAllPieces[i]->getPosition();
                                    end = vec[j];
                                }
                            }
                        }
                        
                    }
                }

                return maxEval;
            }
        }
};


#endif