#ifndef KNIGHT_HPP_
#define KNIGHT_HPP_

#include "chessman.hpp"


class Knight : public Chessman
{
    public:
        using Chessman::Chessman;
        bool makeMove(char column, int row) override;
};

#endif