#ifndef BOARD_HPP_
#define BOARD_HPP_

#include "chessman.hpp"
#include "pawn.hpp"
#include "queen.hpp"
#include <vector>
#include <memory>
#include <iostream>

class Board
{   
    protected:
        /* Macierz przechowująca wskaźniki na każde pole planszy */
        std::vector<std::vector<std::shared_ptr<Chessman>>> board;

    public:
        /* Bezparametryczny konstruktor planszy.
            Przypisuje odpowiednim miejscom na planszy pionki */
        Board();

        /* Funkcja resetująca planszę działanie podobne do konstruktora */
        void resetBoard();

        /* Funkcja zwraca referencję do macierzy */
        std::vector<std::vector<std::shared_ptr<Chessman>>>& getBoard();

        /* Funkcja pozwala zmienić zwraca wskaźnik na figurę */
        std::shared_ptr<Chessman>& changePiece(int column, int row);
};

#endif