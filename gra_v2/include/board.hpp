#ifndef BOARD_HPP_
#define BOARD_HPP_

#include "chessman.hpp"
#include "pawn.hpp"
#include "queen.hpp"
#include <vector>
#include <memory>
#include <iostream>

class Board
{   
    protected:
        std::vector<std::vector<std::shared_ptr<Chessman>>> board;

    public:
        Board();
        void resetBoard();
        std::vector<std::vector<std::shared_ptr<Chessman>>>& getBoard();
        std::shared_ptr<Chessman>& changePiece(int column, int row);
};

#endif