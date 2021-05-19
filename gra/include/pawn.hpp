#ifndef PAWN_HPP_
#define PAWN_HPP_

#include "chessman.hpp"


class Pawn : public Chessman
{
    public:
        using Chessman::Chessman;
        bool makeMove(char column, int row) override;
};

#endif