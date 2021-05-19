#ifndef BOARD_HPP_
#define BOARD_HPP_

#include "chessman.hpp"
#include <vector>
#include <memory>

class Board
{
    std::vector<std::vector<std::shared_ptr<Chessman>>> board;

    Board()
    {
        for (int i = 0; i < 8; i++)
        {
            std::vector<std::shared_ptr<Chessman>> v;

            std::vector<int> v;
            for (int j = 0; j < 8; j++) {
                v.push_back(nullptr);
            }

            board.push_back(v);
        }

        
    }
};

#endif