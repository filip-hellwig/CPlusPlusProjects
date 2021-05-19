#ifndef BISHOP_HPP_
#define BISHOP_HPP_

#include "chessman.hpp"


class Bishop : public Chessman
{
    public:
        using Chessman::Chessman;
        bool makeMove(char column, int row) override;
};

#endif