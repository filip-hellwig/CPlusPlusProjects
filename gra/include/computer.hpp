#ifndef COMPUTER_HPP_
#define COMPUTER_HPP_

#include "player.hpp"

class Computer : public Player 
{
    public:
        Computer(bool isWhiteSide)
        {
            whiteSide = isWhiteSide;
            humanPlayer = false;
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