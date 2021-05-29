#ifndef GUI_HPP_
#define GUI_HPP_

#include <SDL.h>
#include <SDL_ttf.h>

class Gui
{
  public:
    bool init();
    void execGame();

  private:
    void draw();
    void mouseButtonDown(SDL_Event& event);

    bool gameIsRunning = false;

    SDL_Window* window = nullptr;
    SDL_Surface* surface = nullptr;
    TTF_Font* font = nullptr;

    SDL_Surface* white_pawn = nullptr;
    SDL_Surface* black_pawn = nullptr;
    SDL_Surface* background = nullptr;
    SDL_Surface* white_bg = nullptr;
    SDL_Surface* dark_tile = nullptr;
    SDL_Surface* pale_tile = nullptr;
};

#endif /* GAME_GUI_HPP_ */
