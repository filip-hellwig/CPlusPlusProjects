#ifndef CHESSMAN_HPP_
#define CHESSMAN_HPP_

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <memory>
#include "position.hpp"
class Player;

class Chessman
{
    protected:
        Position position; 
        bool existance;
        bool white;
    
    public:
        virtual bool makeMove(Position nextMove, std::vector<std::vector<std::shared_ptr<Chessman>>>& board,
                                int& flagQueen, int& pieceNum) = 0;
        virtual std::string name() = 0;


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
            if (column > 7 || row < 0)
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

        /* int flagQueen(int row)
        {
            if((row == 7 && white == true)
                || (row == 0 && white == false))
            {
                static int c = 1;
            } else
            {
                static int c = 0;
            }
            return 0;
        } */

        bool checkMaxJump(Position nextMove, std::vector<std::vector<std::shared_ptr<Chessman>>>& board)
        {
            int i = 0;
            Position pos;

            if (checkIndexValidity(nextMove.column+2, nextMove.row+2)
                && board[nextMove.column+1][nextMove.row+1] != nullptr
                && board[nextMove.column+1][nextMove.row+1]->getWhite() != white
                && (board[nextMove.column+2][nextMove.row+2] == nullptr
                || (board[nextMove.column+2][nextMove.row+2] != nullptr
                && pos.setPostition(nextMove.column+2, nextMove.row+2) == position)))
            { i++; }
            if (checkIndexValidity(nextMove.column-2, nextMove.row+2)
                && board[nextMove.column-1][nextMove.row+1] != nullptr
                && board[nextMove.column-1][nextMove.row+1]->getWhite() != white
                && (board[nextMove.column-2][nextMove.row+2] == nullptr
                || (board[nextMove.column-2][nextMove.row+2] != nullptr
                && pos.setPostition(nextMove.column-2, nextMove.row+2) == position)))
            { i++; }
            if (checkIndexValidity(nextMove.column+2, nextMove.row-2)
                && board[nextMove.column+1][nextMove.row-1] != nullptr
                && board[nextMove.column+1][nextMove.row-1]->getWhite() != white
                && (board[nextMove.column+2][nextMove.row-2] == nullptr
                || (board[nextMove.column+2][nextMove.row-2] != nullptr
                && pos.setPostition(nextMove.column+2, nextMove.row-2) == position)))
            { i++; }
            if (checkIndexValidity(nextMove.column-2, nextMove.row-2)
                && board[nextMove.column-1][nextMove.row-1] != nullptr
                && board[nextMove.column-1][nextMove.row-1]->getWhite() != white
                && (board[nextMove.column-2][nextMove.row-2] == nullptr
                || (board[nextMove.column-2][nextMove.row-2] != nullptr
                && pos.setPostition(nextMove.column-2, nextMove.row-2) == position)))
            { i++; }

            if (i > 1) { return false; }
            else { return true; } 
        }


        bool checkJumping(Position nextMove, std::vector<std::vector<std::shared_ptr<Chessman>>>& board, int& flagQueen, int& pieceNum)
        {
            Position newPosition;
            std::shared_ptr<Chessman> histPiece;

            if (checkIndexValidity(nextMove.column+2, nextMove.row+2)
                && board[nextMove.column+1][nextMove.row+1] != nullptr
                && board[nextMove.column+1][nextMove.row+1]->getWhite() != white)
            {
                if (board[nextMove.column+2][nextMove.row+2] != nullptr)
                {
                    if (newPosition.setPostition(nextMove.column+2, nextMove.row+2) == position)
                    {
                        board[nextMove.column+1][nextMove.row+1]->changeExistance(false);
                        board[nextMove.column+1][nextMove.row+1] = nullptr;
                        pieceNum -= 1;
                        return true;
                    }
                } else 
                {
                    board[nextMove.column+1][nextMove.row+1]->changeExistance(false);
                    histPiece = board[nextMove.column+1][nextMove.row+1];
                    board[nextMove.column+1][nextMove.row+1] = nullptr;
                    pieceNum -= 1;

                    
                    if(checkJumping(newPosition.setPostition(nextMove.column+2, nextMove.row+2), board, flagQueen, pieceNum))
                    {
                        if((nextMove.row+2 == 7 && white == true)
                            || (nextMove.row+2 == 0 && white == false))
                        {
                            flagQueen = 1;
                        }
                        return true;
                    }

                    board[nextMove.column+1][nextMove.row+1] = histPiece;
                    board[nextMove.column+1][nextMove.row+1]->changeExistance(true);
                    histPiece = nullptr;
                    pieceNum += 1;
                }
            }
            if (checkIndexValidity(nextMove.column-2, nextMove.row+2)
                && board[nextMove.column-1][nextMove.row+1] != nullptr
                && board[nextMove.column-1][nextMove.row+1]->getWhite() != white)
            {
                if (board[nextMove.column-2][nextMove.row+2] != nullptr)
                {
                    if (newPosition.setPostition(nextMove.column-2, nextMove.row+2) == position)
                    {
                        board[nextMove.column-1][nextMove.row+1]->changeExistance(false);
                        board[nextMove.column-1][nextMove.row+1] = nullptr;
                        pieceNum -= 1;
                        return true;
                    }
                } else 
                {
                    board[nextMove.column-1][nextMove.row+1]->changeExistance(false);
                    histPiece = board[nextMove.column-1][nextMove.row+1];
                    board[nextMove.column-1][nextMove.row+1] = nullptr;
                    pieceNum -= 1;

                    
                    if(checkJumping(newPosition.setPostition(nextMove.column-2, nextMove.row+2), board, flagQueen, pieceNum))
                    {
                        if((nextMove.row+2 == 7 && white == true)
                            || (nextMove.row+2 == 0 && white == false))
                        {
                            flagQueen = 1;
                        }
                        return true;
                    }

                    board[nextMove.column-1][nextMove.row+1] = histPiece;
                    board[nextMove.column-1][nextMove.row+1]->changeExistance(true);
                    histPiece = nullptr;
                    pieceNum += 1;
                }
            }
            if (checkIndexValidity(nextMove.column+2, nextMove.row-2)
                && board[nextMove.column+1][nextMove.row-1] != nullptr
                && board[nextMove.column+1][nextMove.row-1]->getWhite() != white)
            {
                if (board[nextMove.column+2][nextMove.row-2] != nullptr)
                {
                    if (newPosition.setPostition(nextMove.column+2, nextMove.row-2) == position)
                    {
                        board[nextMove.column+1][nextMove.row-1]->changeExistance(false);
                        board[nextMove.column+1][nextMove.row-1] = nullptr;
                        pieceNum -= 1;
                        return true;
                        
                    }
                } else 
                {
                    board[nextMove.column+1][nextMove.row-1]->changeExistance(false);
                    histPiece = board[nextMove.column-1][nextMove.row+1];
                    board[nextMove.column+1][nextMove.row-1] = nullptr;
                    pieceNum -= 1;

                    
                    if(checkJumping(newPosition.setPostition(nextMove.column+2, nextMove.row-2), board, flagQueen, pieceNum))
                    {
                        if((nextMove.row-2 == 7 && white == true)
                            || (nextMove.row-2 == 0 && white == false))
                        {
                            flagQueen = 1;
                        }
                        return true;
                    }

                    board[nextMove.column+1][nextMove.row-1] = histPiece;
                    board[nextMove.column+1][nextMove.row-1]->changeExistance(true);
                    histPiece = nullptr;
                    pieceNum += 1;
                }
            }
            if (checkIndexValidity(nextMove.column-2, nextMove.row-2)
                && board[nextMove.column-1][nextMove.row-1] != nullptr
                && board[nextMove.column-1][nextMove.row-1]->getWhite() != white)
            {
                if (board[nextMove.column-2][nextMove.row-2] != nullptr)
                {
                    if (newPosition.setPostition(nextMove.column-2, nextMove.row-2) == position)
                    {
                        board[nextMove.column-1][nextMove.row-1]->changeExistance(false);
                        board[nextMove.column-1][nextMove.row-1] = nullptr;
                        pieceNum -= 1;
                        return true;
                    }
                } else 
                {
                    board[nextMove.column-1][nextMove.row-1]->changeExistance(false);
                    histPiece = board[nextMove.column-1][nextMove.row-1];
                    board[nextMove.column-1][nextMove.row-1] = nullptr;
                    pieceNum -= 1;

                    
                    if(checkJumping(newPosition.setPostition(nextMove.column-2, nextMove.row-2), board, flagQueen, pieceNum))
                    {
                        if((nextMove.row-2 == 7 && white == true)
                            || (nextMove.row-2 == 0 && white == false))
                        {
                            flagQueen = 1;
                        }
                        return true;
                    }

                    board[nextMove.column-1][nextMove.row-1] = histPiece;
                    board[nextMove.column-1][nextMove.row-1]->changeExistance(true);
                    histPiece = nullptr;
                    pieceNum += 1;
                }
            }
            return false;
        }

};


#endif