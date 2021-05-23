#ifndef KNIGHT_HPP_
#define KNIGHT_HPP_

#include "chessman.hpp"


class Knight : public Chessman
{
    public:
        using Chessman::Chessman;
        bool makeMove(int column, int row, std::vector<std::vector<std::shared_ptr<Chessman>>> board) override;
        std::string name() override;
};

#endif