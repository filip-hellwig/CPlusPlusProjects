#ifndef HUMAN_HPP_
#define HUMAN_HPP_

#include "player.hpp"

/* Klasa wyspecializowana dla przeciwnika będącego człowiekiem */
class Human : public Player 
{  
    public:
        /* Konstruktor parametryczny klasy Human. Przypisuje graczowi kolor, 
            oraz odpowiednie figury z planszy. */
        Human(bool isWhiteSide, std::vector<std::vector<std::shared_ptr<Chessman>>> board)
        {
            whiteSide = isWhiteSide;
            humanPlayer = true;

            for (int i = 0; i < 8; i++)
            {
                allPieces.push_back(nullptr);
            }

            if (whiteSide)
            {
                allPieces[0] = board[0][0];
                allPieces[1] = board[1][1];
                allPieces[2] = board[2][0];
                allPieces[3] = board[3][1];
                allPieces[4] = board[4][0];
                allPieces[5] = board[5][1];
                allPieces[6] = board[6][0];
                allPieces[7] = board[7][1];
            } else
            {
                allPieces[0] = board[0][6];
                allPieces[1] = board[1][7];
                allPieces[2] = board[2][6];
                allPieces[3] = board[3][7];
                allPieces[4] = board[4][6];
                allPieces[5] = board[5][7];
                allPieces[6] = board[6][6];
                allPieces[7] = board[7][7];
            }
        }

        /* Operator porównania dwóch graczy */
        bool operator==(Player p)
        {
            if (whiteSide == p.isWhiteSide())
            {
                return true;
            } else
            {
                return false;
            }
        }
};

#endif