#ifndef QUEEN_HPP_
#define QUEEN_HPP_

#include "chessman.hpp"


class Queen : public Chessman
{
    public:
        using Chessman::Chessman;
        bool makeMove(char column, int row) override;
};

#endif