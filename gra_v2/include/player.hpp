#ifndef PLAYER_HPP_
#define PLAYER_HPP_ 

#include <list>

class Player 
{
    public: 
        bool whiteSide;
        bool humanPlayer;
        int pieceNum = 8;
    
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
};

#endif