#ifndef PLAYER_HPP_
#define PLAYER_HPP_ 

#include <vector>
#include <memory>
#include "chessman.hpp"

class Chessman;

class Player 
{
    protected: 
        bool whiteSide;
        bool humanPlayer;
        int pieceNum = 8;
        std::vector<std::shared_ptr<Chessman>> allPieces;
    
    public:
        bool isWhiteSide()
        {
            return whiteSide;
        }
        bool isHumanPlayer()
        {
            return humanPlayer;
        }
        int& getPieceNum()
        {
            return pieceNum;
        }
        void modifyPieceNum(int i)
        {
            pieceNum += i;
        }

        bool isMoveImpossible(std::vector<std::vector<std::shared_ptr<Chessman>>>& board)
        {
            Position pos;
            std::vector<Position> vec = pos.allPostitons();

            for(int i = 0; i < 8; i++)
            {
                if (allPieces[i]->getExistance() == true)
                {
                    for (int j = 0; j < 32; j++)
                    {
                        if (allPieces[i]->checkMove(vec[j], board))
                        {
                            return false;
                        }
                    }
                    
                }
            }

            return true;
        }
        
};

#endif