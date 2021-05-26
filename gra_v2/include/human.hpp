#ifndef HUMAN_HPP_
#define HUMAN_HPP_

#include "player.hpp"

class Human : public Player 
{  
    public:
        Human(bool isWhiteSide)
        {
            whiteSide = isWhiteSide;
            humanPlayer = true;
        }

        bool operator==(Player p)
        {
            if (whiteSide == p.isWhiteSide())
            {
                return true;
            } else
            {
                return false;
            }
        }
};

#endif