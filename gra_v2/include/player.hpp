#ifndef PLAYER_HPP_
#define PLAYER_HPP_ 

#include <vector>
#include <memory>
#include "chessman.hpp"

class Chessman;


/* Klasa definiuje gracza */
class Player 
{
    protected: 
        /* Czy gracz gra białymi */
        bool whiteSide;

        /* Czy gracz jest człowiekiem */
        bool humanPlayer;

        /* Ilość aktywnych figur gracza */
        int pieceNum = 8;

        /* Wektor przechowujący wskaźniki na wszystkie figury gracza */
        std::vector<std::shared_ptr<Chessman>> allPieces;
    
    public:
        bool isWhiteSide()
        {
            return whiteSide;
        }

        bool isHumanPlayer()
        {
            return humanPlayer;
        }

        int& getPieceNum()
        {
            return pieceNum;
        }

        std::vector<std::shared_ptr<Chessman>>& getAllPieces()
        {
            return allPieces;
        }

        /* Funkcja resetuje gracza. Po resecie planszy przypisuje graczowi odpowiednie figury,
            oraz ustawia ich poprawną liczbę */
        void resetPlayer(std::vector<std::vector<std::shared_ptr<Chessman>>> board)
        {
            pieceNum = 8;

            for (int i = 0; i < 8; i++)
            {
                allPieces[i] = nullptr;
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

        /* Funkcja przypisuje nullptr wszystkim figurom gracza. 
            Funkcja służy do zmieniania przeciwników na planszy */
        void nullPlayer()
        {
            pieceNum = 8;

            for (int i = 0; i < 8; i++)
            {
                allPieces[i] = nullptr;
            }
        }

        /* Funkcja sprawdza czy dany gracz może wykonać jakikolwiek ruch */
        bool isMoveImpossible(std::vector<std::vector<std::shared_ptr<Chessman>>>& board)
        {
            Position pos;
            std::vector<Position> vec = pos.allPostitons();

            for(int i = 0; i < 8; i++)
            {
                if (allPieces[i]->getExistance())
                {
                    for (int j = 0; j < 32; j++)
                    {
                        if (allPieces[i]->checkMove(vec[j], board))
                        {
                            return false;
                        }
                    }
                    
                }
            }

            return true;
        }
};

#endif