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
    bool init();
    void execGame();

  private:
    void draw(std::vector<std::vector<std::shared_ptr<Chessman>>>& board);
    void initBoard();
    void generateBoard();
    void generateChessman(int column, int row, std::vector<std::vector<std::shared_ptr<Chessman>>>& board);
    void drawPick(Position& pos, std::vector<std::vector<std::shared_ptr<Chessman>>>& board);
    void unDrawPick(Position& pos, std::vector<std::vector<std::shared_ptr<Chessman>>>& board);
    void mouseButtonDown(SDL_Event& event, Position& begin, Position& end, Board& b,
                          bool white, std::shared_ptr<Player>& currentTurn, std::shared_ptr<Player>& opponent, std::shared_ptr<Player>& additional);
    void returnDown(Position& begin, Position& end, Board& b, int& flagQueen,
                    std::shared_ptr<Player>& currentTurn, std::shared_ptr<Player>& opponent);
    void pickTile(int y, int x, Position& pos);
    void pickButton(int y, int x, Position& begin, Position& end, Board& b,
                      std::shared_ptr<Player>& currentTurn, std::shared_ptr<Player>& opponent, std::shared_ptr<Player>& additional);

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

#endif /* GAME_GUI_HPP_ */
