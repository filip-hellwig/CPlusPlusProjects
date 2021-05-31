#ifndef QUEEN_HPP_
#define QUEEN_HPP_

#include "chessman.hpp"


class Queen : public Chessman
{
    public:
        using Chessman::Chessman;
        bool makeMove(Position nextMove, std::vector<std::vector<std::shared_ptr<Chessman>>>& board,
                        int& flagQueen, int& pieceNum) override;
        bool checkMove(Position nextMove, std::vector<std::vector<std::shared_ptr<Chessman>>>& board) override;
        bool isQueen() override;
};

#endif