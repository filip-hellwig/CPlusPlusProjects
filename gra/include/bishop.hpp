#ifndef BISHOP_HPP_
#define BISHOP_HPP_

#include "chessman.hpp"


class Bishop : public Chessman
{
    public:
        using Chessman::Chessman;
        bool makeMove(int column, int row, std::vector<std::vector<std::shared_ptr<Chessman>>> board) override;
        std::string name() override;
};

#endif