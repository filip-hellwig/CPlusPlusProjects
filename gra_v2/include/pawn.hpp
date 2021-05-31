#ifndef PAWN_HPP_
#define PAWN_HPP_

#include "chessman.hpp"


class Pawn : public Chessman
{
    public:
        using Chessman::Chessman;
        bool makeMove(Position nextMove, std::vector<std::vector<std::shared_ptr<Chessman>>>& board,
                        int& flagQueen, int& pieceNum) override;
        bool checkMove(Position nextMove, std::vector<std::vector<std::shared_ptr<Chessman>>>& board) override;
        bool isQueen() override;
};

#endif