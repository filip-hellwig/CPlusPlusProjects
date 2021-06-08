#ifndef QUEEN_HPP_
#define QUEEN_HPP_

#include "chessman.hpp"


class Queen : public Chessman
{
    public:
        using Chessman::Chessman;
        bool makeMove(Position nextMove, std::vector<std::vector<std::shared_ptr<Chessman>>>& board,
                        bool& flagQueen, int& pieceNum) override;
        bool checkMove(Position nextMove, std::vector<std::vector<std::shared_ptr<Chessman>>>& board) override;
        int minmaxMove(std::vector<std::vector<std::shared_ptr<Chessman>>>& board, int& currentTurnPieceNum,
                        int& opponentPieceNum, std::vector<std::shared_ptr<Chessman>>& currentTurnAllPieces,
                        std::vector<std::shared_ptr<Chessman>>& opponentAllPieces, int depth, bool maxingPlayer,
                        Position& begin, Position& end, Position nextMove) override;
        int partMinmaxMove(std::vector<std::vector<std::shared_ptr<Chessman>>>& board, int& currentTurnPieceNum,
                                int& opponentPieceNum, std::vector<std::shared_ptr<Chessman>>& currentTurnAllPieces,
                                std::vector<std::shared_ptr<Chessman>>& opponentAllPieces, int depth, bool maxingPlayer,                        
                                Position& begin, Position& end, Position nextMove) override;
        bool isQueen() override;
};

#endif