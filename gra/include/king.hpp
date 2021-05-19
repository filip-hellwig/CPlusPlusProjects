#ifndef KING_HPP_
#define KING_HPP_

#include "chessman.hpp"


class King : public Chessman
{
    public:
        using Chessman::Chessman;
        bool makeMove(char column, int row) override;
};

#endif