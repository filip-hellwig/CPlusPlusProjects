#ifndef ROOK_HPP_
#define ROOK_HPP_

#include "chessman.hpp"


class Rook : public Chessman
{
    public:
        using Chessman::Chessman;
        bool makeMove(char column, int row) override;
};

#endif