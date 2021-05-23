#ifndef BOARD_HPP_
#define BOARD_HPP_

#include "chessman.hpp"
#include "bishop.hpp"
#include "king.hpp"
#include "knight.hpp"
#include "pawn.hpp"
#include "queen.hpp"
#include "rook.hpp"
#include <vector>
#include <memory>
#include <iostream>

class Board
{   
    protected:
        std::vector<std::vector<std::shared_ptr<Chessman>>> board;

    public:
        Board();
        void showBoard();
        std::vector<std::vector<std::shared_ptr<Chessman>>> getBoard();
        std::shared_ptr<Chessman> changePiece(int column, int row);
};

#endif