#ifndef KING_HPP_
#define KING_HPP_

#include "chessman.hpp"


class King : public Chessman
{
    public:
        using Chessman::Chessman;
        bool makeMove(int column, int row, std::vector<std::vector<std::shared_ptr<Chessman>>> board) override;
        std::string name() override;
};

#endif