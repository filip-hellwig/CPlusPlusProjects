#ifndef GUI_HPP_
#define GUI_HPP_

#include <SDL.h>
#include <SDL_ttf.h>
#include <unistd.h>
#include <iostream>

#include "pawn.hpp"
#include "queen.hpp"
#include "board.hpp"
#include "human.hpp"
#include "computer.hpp"


class Gui
{
  public:
    /* Funkcja inicializująca całą grę */
    bool init();

    /* Funkcja która przeprowadza grę  */
    void execGame();

  private:
    /* Funkcja generująca czystą planszę */
    void generateBoard();
    
    /* Funkcja generująca figury w odpowiednich polach planszy */
    void generateChessman(int column, int row, std::vector<std::vector<std::shared_ptr<Chessman>>>& board);

    /* Funkcja rysująca planszę oraz figury na niej */
    void draw(std::vector<std::vector<std::shared_ptr<Chessman>>>& board);

    /* Funkcja rysująca wybranie odpowiedniego pola na planszy */
    void drawPick(Position& pos, std::vector<std::vector<std::shared_ptr<Chessman>>>& board);

    /* Funkcja wymazująca wybranie odpowiedniego pola na planszy */
    void unDrawPick(Position& pos, std::vector<std::vector<std::shared_ptr<Chessman>>>& board);

    /* Funkcja rysująca wybranie odpowiedniego przycisku */
    void drawButton(std::shared_ptr<Player>& opponent);

    /* Funkcja przetwarzająca wybór miejsca na planszy.
        Dla odpowienich współrzędnych przypisuje odpowiednią pozycję na planszy. */
    void pickTile(int y, int x, Position& pos);

    /* Funkcja przetwarzająca wybór przycisku z planszy.
        Dla odpowiednich współrzednych wybiera odpowiedni przycisk z planszy. */
    void pickButton(int y, int x, Position& begin, Position& end, Board& b,
                      std::shared_ptr<Player>& currentTurn, std::shared_ptr<Player>& opponent, 
                      std::shared_ptr<Player>& additional);

    /* Funkcja przetwarzająca przyciski myszy.
        Dla lewego przycisku myszy wybiera pozycję początkową lub końcową,
        lub wybiera odpowiedni przycisk.
        Dla prawego przycisku cofa wybranie pozycji początkowej lub końcowej. */
    void mouseButtonDown(SDL_Event& event, Position& begin, Position& end, Board& b,
                          bool white, std::shared_ptr<Player>& currentTurn, 
                          std::shared_ptr<Player>& opponent, std::shared_ptr<Player>& additional);

    /* Funkcja przetwarzająca klawiaturę.
        W przypadku wciśnięcia przycisku "Return", gra wykonuje ruch wybrany przez gracza
        oraz obsługuje poprawne ustawienie pionków oraz graczy, jednocześnie wyświetlając
        planszę. */                          
    void returnDown(Position& begin, Position& end, Board& b, bool& flagQueen,
                    std::shared_ptr<Player>& currentTurn, std::shared_ptr<Player>& opponent);

    /* Funkcja inicializująca okno gry */
    void initBoard();


    /* Zmienne wykorzystywane w działaniu programy */
    bool gameIsRunning = false;

    SDL_Window* window = nullptr;
    SDL_Surface* surface = nullptr;
    TTF_Font* font = nullptr;
    TTF_Font* fontSmall = nullptr;

    SDL_Surface* white_pawn = nullptr;
    SDL_Surface* black_pawn = nullptr;
    SDL_Surface* white_queen = nullptr;
    SDL_Surface* black_queen = nullptr;
    SDL_Surface* background = nullptr;
    SDL_Surface* white_bg = nullptr;
    SDL_Surface* dark_tile = nullptr;
    SDL_Surface* pale_tile = nullptr;
    SDL_Surface* pale_tile_pick = nullptr;
    SDL_Surface* dark_tile_pick = nullptr;
};

#endif /* GUI_HPP_ */
