#ifndef PLAYER_HPP_
#define PLAYER_HPP_ 

class Player 
{
    public: 
        bool whiteSide;
        bool humanPlayer;
    
        bool isWhiteSide()
        {
            return whiteSide;
        }
        bool isHumanPlayer()
        {
            return humanPlayer;
        }
};

#endif