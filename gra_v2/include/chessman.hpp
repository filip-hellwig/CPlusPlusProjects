#ifndef CHESSMAN_HPP_
#define CHESSMAN_HPP_

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <memory>
#include "position.hpp"

class Chessman
{
    protected:
        Position position; 
        bool existance;
        bool white;
    
    public:
        virtual bool makeMove(Position nextMove, std::vector<std::vector<std::shared_ptr<Chessman>>>& board,
                                int& flagQueen, int& pieceNum ) = 0;
        virtual bool checkMove(Position nextMove, std::vector<std::vector<std::shared_ptr<Chessman>>>& board) = 0;                           
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
                            if((row2 == 7 && white == true)
                                || (row2 == 0 && white == false))
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

};


#endif