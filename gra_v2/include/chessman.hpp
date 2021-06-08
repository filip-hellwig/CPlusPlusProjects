#ifndef CHESSMAN_HPP_
#define CHESSMAN_HPP_

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <memory>
#include "position.hpp"

#define INFI 20000


class Player;


/* Klasa wirtualna będąca podstawą dla klas Pawn oraz Queen.
    Zawiera uniwersalne funkcje dla obu klas. */
class Chessman
{
    protected:
        /* Pozycja figury na plaszny */
        Position position;

        /* Czy figura istnieje */ 
        bool existance;

        /* Czy figura jest biała */
        bool white;
    
    public:
        /* 
            Funkcja służąca do wykonywania ruchu przez człowieka.
            Funkcja sprawdza czy dana figura jest wstanie osiągnąć daną pozycję końcową,
            jeżeli jest to możliwe to funkcja zwraca true oraz zmienia pozycją figury na nową pozycję.
            Jeżeli ruch zawierał bicie, to funkcja usuwa pionki przeciwnika z planszy. Funkcja sprawdza również
            czy dany pionek powinien zostać zamieniony na królową.
        */
        virtual bool makeMove(Position nextMove, std::vector<std::vector<std::shared_ptr<Chessman>>>& board,
                                bool& flagQueen, int& pieceNum ) = 0;

        /* 
            Funkcja służąca do sprawdzania czy dany gracz jest w stanie wykonać dany ruch.
            Jeżeli ruch jest możliwy to funkcja zwraca true. 
        */                                
        virtual bool checkMove(Position nextMove, std::vector<std::vector<std::shared_ptr<Chessman>>>& board) = 0;

        /* 
            Funkcja jest rozwinięciem funkcji minmax. Wykonuje ona ruch w specialny sposób,
            zaprojektowany dla ruchu z algorytmem minmax. Jeżeli ruch jest możliwy to funkcja rekurencyjnie uruchamia
            następne wywołanie algorytmu minmax. Natępnie wykonany ruch jest cofany.
        */
        virtual int minmaxMove(std::vector<std::vector<std::shared_ptr<Chessman>>>& board, int& currentTurnPieceNum,
                                int& opponentPieceNum, std::vector<std::shared_ptr<Chessman>>& currentTurnAllPieces,
                                std::vector<std::shared_ptr<Chessman>>& opponentAllPieces, int depth, bool maxingPlayer,
                                Position& begin, Position& end, Position nextMove) = 0;

        /* Funkcja skraca zapis funkcji minmaxMove */                                
        virtual int partMinmaxMove(std::vector<std::vector<std::shared_ptr<Chessman>>>& board, int& currentTurnPieceNum,
                                int& opponentPieceNum, std::vector<std::shared_ptr<Chessman>>& currentTurnAllPieces,
                                std::vector<std::shared_ptr<Chessman>>& opponentAllPieces, int depth, bool maxingPlayer,                        
                                Position& begin, Position& end, Position nextMove) = 0;

        /* Czy figura jest królową */                                                                                       
        virtual bool isQueen() = 0;

        /* Kontruktor parametryczny figury. Ustawia nową pozycję na planszy,
            oraz przypisuje odpowiedni kolor do figury. */
        Chessman(int column, int row, bool isWhite)
        {
            Position newPosition(column, row);
            position = newPosition;
            existance = true;
            white = isWhite;
        }        

        bool getWhite() { return white; }

        bool getExistance() { return existance; }

        void changeExistance(bool b)
        {
            existance = b;
        }

        Position getPosition()
        {
            return position;
        }

        /* Funkcja oblicza wartość wszystkich figur gracza */
        int allPiecesValue(std::vector<std::shared_ptr<Chessman>> all)
        {
            int result = 0;

            for(int i = 0; i < 8; i++)
            {
                if(all[i]->getExistance())
                {
                    if(all[i]->isQueen()) { result += 3; }
                    else { result += 1; }
                }
            }

            return result;
        }

        /* Funkcja sprawdza czy dany ruch mieści się w granicach planszy*/
        bool checkIndexValidity(int column, int row)
        {
            if (row > 7 || row < 0)
            {
                return false;
            }
            if (column > 7 || column < 0)
            {
                return false;
            }
            return true;
        }



        /* Funkcja rozwija funkcję checkMaxJump */
        bool checkMaxJumpShort(int column, int row, int column2, int row2,
                                std::vector<std::vector<std::shared_ptr<Chessman>>>& board)
        {
            Position pos;

            if (checkIndexValidity(column2, row2))
            {
                /* 
                    Sprawdzamy czy:
                    - jest jakaś figura do przeskoczenia
                    - czy ta figura jest innego koloru
                    - czy na miejscu na które skaczemy nie ma figury
                    - jeżeli jest tam coś to czy jest to figura którą ruszamy 
                */
                if(board[column][row] != nullptr
                    && board[column][row]->getWhite() != white
                    && (board[column2][row2] == nullptr
                    || (board[column2][row2] != nullptr
                    && pos.setPostition(column2, row2) == position)))
                { return true; }
            }

            return false;
        }

        /* Funkcja sprawdza czy dana pozycja końcowa nie ma jeszcze możliwości skoku.
            Jeżeli nie ma to zwraca się false. */
        bool checkMaxJump(Position nextMove, std::vector<std::vector<std::shared_ptr<Chessman>>>& board)
        {
            int i = 0;
            if (nextMove == position) { return true; }

            /* Sprawdzamy wszystkie rogi po kolei */
            if (checkMaxJumpShort(nextMove.column+1, nextMove.row+1, nextMove.column+2, nextMove.row+2, board))
            { i++; }
            if (checkMaxJumpShort(nextMove.column-1, nextMove.row+1, nextMove.column-2, nextMove.row+2, board))
            { i++; }
            if (checkMaxJumpShort(nextMove.column+1, nextMove.row-1, nextMove.column+2, nextMove.row-2, board))
            { i++; }
            if (checkMaxJumpShort(nextMove.column-1, nextMove.row-1, nextMove.column-2, nextMove.row-2, board))
            { i++; }

            if (i > 1) { return false; }
            else { return true; } 
        }



        /* Funkcja rozwija funkcję makeJump */
        bool makeJumpShort(int column, int row, int column2, int row2,
                                std::vector<std::vector<std::shared_ptr<Chessman>>>& board,
                                bool& flagQueen, int& pieceNum)
        {
            Position newPosition;
            std::shared_ptr<Chessman> histPiece;

            if (checkIndexValidity(column2, row2))
            {   
                /* Sprawdzamy czy jest jakaś figura do przeskoczenia
                    i czy jest to figura przeciwnika */
                if(board[column][row] != nullptr
                && board[column][row]->getWhite() != white)
                {   
                    if (board[column2][row2] != nullptr)
                    {
                        /* Przypadek bazowy.
                            Sprawdzamy czy doszliśmy na pozycję figury którą ruszamy. */
                        if (newPosition.setPostition(column2, row2) == position)
                        {
                            /* Usuwamy przeskoczoną figurę z planszy */
                            board[column][row]->changeExistance(false);
                            board[column][row] = nullptr;
                            pieceNum += -1;

                            return true;
                        }
                    } else 
                    {
                        /* Usuwamy przeskoczoną figurę z planszy */
                        board[column][row]->changeExistance(false);
                        histPiece = board[column][row];
                        board[column][row] = nullptr;
                        pieceNum += -1;
                        
                        if(makeJump(newPosition.setPostition(column2, row2), board, flagQueen, pieceNum))
                        {
                            /* Jeżeli pionek ma się stać królową */
                            if((row2 == 7 && white)
                                || (row2 == 0 && !white))
                            {
                                flagQueen = true;
                            }
                            return true;
                        }

                        /* Jeżeli ruch nie jest możliwy to przywracamy usuniętą figurę na planszę */
                        board[column][row] = histPiece;
                        board[column][row]->changeExistance(true);
                        histPiece = nullptr;
                        pieceNum += 1;
                    }
                }
            }
            return false;
        }

        /* 
            Funkcja sprawdza czy dana figura jest wstanie osiągnąć daną pozycję końcową skokiem,
            jeżeli jest to możliwe to funkcja zwraca true oraz zmienia pozycją figury na nową pozycję.
            Funkcja usuwa pionki przeciwnika z planszy. Sprawdza również
            czy dany pionek powinien zostać zamieniony na królową.
            Jest to algorytm rekurencyjny, który zaczyna na miejscu końcowym naszego ruchu i sprawdza czy możliwe
            jest dojście do figury którą chcemy ruszyć.
        */
        bool makeJump(Position nextMove, std::vector<std::vector<std::shared_ptr<Chessman>>>& board,
                            bool& flagQueen, int& pieceNum)
        {
            if(makeJumpShort(nextMove.column+1, nextMove.row+1, nextMove.column+2, nextMove.row+2,
                                    board, flagQueen, pieceNum))
            { return true; }
            if(makeJumpShort(nextMove.column-1, nextMove.row+1, nextMove.column-2, nextMove.row+2,
                                    board, flagQueen, pieceNum))
            { return true; }
            if(makeJumpShort(nextMove.column+1, nextMove.row-1, nextMove.column+2, nextMove.row-2,
                                    board, flagQueen, pieceNum))
            { return true; }
            if(makeJumpShort(nextMove.column-1, nextMove.row-1, nextMove.column-2, nextMove.row-2,
                                    board, flagQueen, pieceNum))
            { return true; }
            return false;
        }


        /* Funkcja rozwija funkcję checkJump */
        bool checkJumpShort(int column, int row, int column2, int row2,
                                std::vector<std::vector<std::shared_ptr<Chessman>>>& board)
        {
            Position newPosition;
            std::shared_ptr<Chessman> histPiece;

            /* Sprawdzamy czy jest jakaś figura do przeskoczenia
                i czy jest to figura przeciwnika */
            if (checkIndexValidity(column2, row2)
                && board[column][row] != nullptr
                && board[column][row]->getWhite() != white)
            {
                if (board[column2][row2] != nullptr)
                {   
                    /* Przypadek bazowy.
                        Sprawdzamy czy doszliśmy na pozycję figury którą ruszamy. */
                    if (newPosition.setPostition(column2, row2) == position)
                    {
                        return true;
                    }
                } else 
                {
                    /* Usuwamy przeskoczoną figurę z planszy */
                    board[column][row]->changeExistance(false);
                    histPiece = board[column][row];
                    board[column][row] = nullptr;
                    
                    if(checkJump(newPosition.setPostition(column2, row2), board))
                    {
                        /* Przywracamy usuniętą figurę na planszę */
                        board[column][row] = histPiece;
                        board[column][row]->changeExistance(true);
                        histPiece = nullptr;

                        return true;
                    }

                    /* Jeżeli ruch nie jest możliwy to przywracamy usuniętą figurę na planszę */
                    board[column][row] = histPiece;
                    board[column][row]->changeExistance(true);
                    histPiece = nullptr;
                }
            }
            return false;
        }

        /* 
            Funkcja sprawdza czy dana figura jest wstanie osiągnąć daną pozycję końcową skokiem,
            Jeżeli ruch jest możliwy to funkcja zwraca true. 
        */
        bool checkJump(Position nextMove, std::vector<std::vector<std::shared_ptr<Chessman>>>& board)
        {
            if(checkJumpShort(nextMove.column+1, nextMove.row+1, nextMove.column+2, nextMove.row+2,
                                    board))
            { return true; }
            if(checkJumpShort(nextMove.column-1, nextMove.row+1, nextMove.column-2, nextMove.row+2,
                                    board))
            { return true; }
            if(checkJumpShort(nextMove.column+1, nextMove.row-1, nextMove.column+2, nextMove.row-2,
                                    board))
            { return true; }
            if(checkJumpShort(nextMove.column-1, nextMove.row-1, nextMove.column-2, nextMove.row-2,
                                    board))
            { return true; }
            return false;
        }

        /* 
            Funkcja służąca do szukania najlepszego ruchu. Jest to algorytm oparty o zasadę minmax.
            Szuka on z pośród wszytkich możliwych opcji figurę początkową oraz miejsce przesunięcia tej figury
            które minimalizuje liczbę figur przeciwnika oraz maksymalizuje liczbę liczbę figur komputera.
            Królowa ma wartość trzykrotnie większą od pionka.
            Funkcja zwraca liczbę figur przeciwnikia pomniejszoną o liczbę figur komputera. Funkcja zmienia również
            zmienne begin oraz end zgodnie z najlepszym możliwym ruchem. 
        */
        int minmax(std::vector<std::vector<std::shared_ptr<Chessman>>>& board, int& currentTurnPieceNum,
                    int& opponentPieceNum, std::vector<std::shared_ptr<Chessman>>& currentTurnAllPieces,
                    std::vector<std::shared_ptr<Chessman>>& opponentAllPieces, int depth, bool maxingPlayer,
                    Position& begin, Position& end, Position nextMove) 
        {
            /* Krok podstawowy.
                Zwraca liczbę 24 pomniejszoną o wartość figur komputera powiększoną o wartość figur przeciwnika */
            if (depth == 0 
                || currentTurnPieceNum == 0
                || opponentPieceNum == 0)
            { return 24-allPiecesValue(currentTurnAllPieces)+allPiecesValue(opponentAllPieces); }
            
            bool noMoveFlag = true;
            Position tempBegin, tempEnd;
            std::vector<Position> vec = begin.allPostitons();

            /* Krok podstawowy.
                Sprawdzamy czy konkretny gracz może wykonać jakikolwiek ruch.
                Jeżeli nie to zwracamy odpowiednią wartość do algorytmu. */
            if(maxingPlayer)
            {
                for(int i = 0; i < 8; i++)
                {
                    if (opponentAllPieces[i]->getExistance())
                    {
                        for (int j = 0; j < 32; j++)
                        {
                            if (opponentAllPieces[i]->checkMove(vec[j], board))
                            {
                                noMoveFlag = false;
                            }
                        }
                        
                    }
                }
                if(noMoveFlag) { return -10; }
            } else
            {
                for(int i = 0; i < 8; i++)
                {
                    if (currentTurnAllPieces[i]->getExistance())
                    {
                        for (int j = 0; j < 32; j++)
                        {
                            if (!currentTurnAllPieces[i]->checkMove(vec[j], board))
                            {
                                noMoveFlag = false;
                            }
                        }
                        
                    }
                }
                if(noMoveFlag) { return 50; }
            }
            
            /* Główna część algorytmu. W zależności od głębokości na jakiej jesteśmy w algorytmie 
                maksymalizujemy lub minimalizujemy rezultat ruchu */
            if (maxingPlayer)
            {
                int minEval = INFI;
                int eval = INFI;

                /* Sprawdzamy wszystkie pionki pod kątem wszystkich możliwych ruchów.
                    Ta część algorytmu próbuje minimalizować. */
                for(int i = 0; i < 8; i++)
                {
                    if (currentTurnAllPieces[i]->getExistance())
                    {
                        for (int j = 0; j < 32; j++)
                        {
                            eval = currentTurnAllPieces[i]->minmaxMove(board, currentTurnPieceNum,
                                                                    opponentPieceNum, currentTurnAllPieces,
                                                                    opponentAllPieces, depth, maxingPlayer,
                                                                    begin, end, vec[j]);
                            {
                                /* -1 oznacza brak możliwości ruchu */
                                if (eval < minEval && eval != -1)
                                {
                                    minEval = eval;
                                    tempBegin = currentTurnAllPieces[i]->getPosition();
                                    tempEnd = vec[j];
                                }
                            }
                        }
                        
                    }
                }

                /* Przypisujemy oryginałom wyznaczone pozycje */ 
                begin = tempBegin;
                end = tempEnd;

                return minEval;
            } else
            {
                int maxEval = -INFI;
                int eval = -INFI;

                /* Sprawdzamy wszystkie pionki pod kątem wszystkich możliwych ruchów.
                    Ta część algorytmu próbuje maksymalizować. */
                for(int i = 0; i < 8; i++)
                {
                    if (opponentAllPieces[i]->getExistance())
                    {
                        for (int j = 0; j < 32; j++)
                        {
                            eval = opponentAllPieces[i]->minmaxMove(board, currentTurnPieceNum,
                                                                    opponentPieceNum, currentTurnAllPieces,
                                                                    opponentAllPieces, depth, maxingPlayer,
                                                                    begin, end, vec[j]);
                            {
                                /* -1 oznacza brak możliwości ruchu */
                                if (eval > maxEval && eval != -1)
                                {
                                    maxEval = eval;
                                    tempBegin = currentTurnAllPieces[i]->getPosition();
                                    tempEnd = vec[j];
                                }
                            }
                        }
                        
                    }
                }

                /* Przypisujemy oryginałom wyznaczone pozycje */
                begin = tempBegin;
                end = tempEnd;
                return maxEval;
            }
        }
};


#endif