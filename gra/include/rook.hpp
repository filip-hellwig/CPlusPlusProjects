#ifndef ROOK_HPP_
#define ROOK_HPP_

#include "chessman.hpp"


class Rook : public Chessman
{
    public:
        using Chessman::Chessman;
        bool makeMove(int column, int row, std::vector<std::vector<std::shared_ptr<Chessman>>> board) override;
        std::string name() override;
};

#endif