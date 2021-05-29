#include "gui.hpp"


bool Gui::init()
{
    int rendererFlags = SDL_RENDERER_ACCELERATED, windowFlags = 0;
    constexpr auto SCREEN_WIDTH = 1280;
    constexpr auto SCREEN_HEIGHT = 1024;

    if(SDL_Init(SDL_INIT_VIDEO) < 0 || TTF_Init() < 0)
    {
        return false;
    }

    window = SDL_CreateWindow("Checkers", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
                              windowFlags);

    if(!window)
    {
        return false;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    surface = SDL_GetWindowSurface(window);

    font = TTF_OpenFont("../data/scpreg.ttf", 36);
    white_pawn = SDL_LoadBMP("../data/white.bmp");
    black_pawn = SDL_LoadBMP("../data/black.bmp");
    background = SDL_LoadBMP("../data/bc.bmp");
    white_bg = SDL_LoadBMP("../data/white_bg.bmp");
    pale_tile = SDL_LoadBMP("../data/pale_tile.bmp");
    dark_tile = SDL_LoadBMP("../data/dark_tile.bmp");

    return surface && font && white_pawn && black_pawn && background && white_bg && pale_tile && dark_tile;
}

void Gui::execGame()
{
    gameIsRunning = true;

    while(gameIsRunning)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    gameIsRunning = false;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    mouseButtonDown(event);
                    break;
            }
        }

        draw();
    }

    SDL_Quit();
    TTF_Quit();
}

void Gui::draw()
{
    SDL_Rect imageRect = {0, 0, 1280, 1024};
    SDL_BlitSurface(background, nullptr, surface, &imageRect);

    SDL_Rect imageRect2 = {112, 112, 824, 824};
    SDL_BlitSurface(white_bg, nullptr, surface, &imageRect2);

    for(int i = 0; i < 8; i+=2)
    {
        for(int j = 0; j < 8; j+=2)
        {
            SDL_Rect imageRect3 = {122+100*i, 122+100*j, 100, 100};
            SDL_BlitSurface(pale_tile, nullptr, surface, &imageRect3);;
        }
    }
    for(int i = 1; i < 8; i+=2)
    {
        for(int j = 1; j < 8; j+=2)
        {
            SDL_Rect imageRect3 = {122+100*i, 122+100*j, 100, 100};
            SDL_BlitSurface(pale_tile, nullptr, surface, &imageRect3);;
        }
    }
    for(int i = 0; i < 8; i+=2)
    {
        for(int j = 0; j < 8; j+=2)
        {
            SDL_Rect imageRect3 = {222+100*i, 122+100*j, 100, 100};
            SDL_BlitSurface(dark_tile, nullptr, surface, &imageRect3);;
        }
    }
    for(int i = 0; i < 8; i+=2)
    {
        for(int j = 0; j < 8; j+=2)
        {
            SDL_Rect imageRect3 = {122+100*i, 222+100*j, 100, 100};
            SDL_BlitSurface(dark_tile, nullptr, surface, &imageRect3);;
        }
    }

    

    SDL_UpdateWindowSurface(window);

    /* SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, 255, 140, 140));
    SDL_Color fontColor = {255, 255, 255};
    SDL_Surface* text = TTF_RenderText_Blended(font, "Welcome to SDL!", fontColor);
    SDL_Rect textRect = {150, 200, text->w, text->h};
    SDL_BlitSurface(text, nullptr, surface, &textRect);
    SDL_FreeSurface(text);
    SDL_Rect imageRect = {400, 500, 60, 60};
    SDL_BlitSurface(white_pawn, nullptr, surface, &imageRect);
    SDL_UpdateWindowSurface(window); */
}

void Gui::mouseButtonDown(SDL_Event& event)
{
    if(event.type == SDL_MOUSEBUTTONDOWN)
    {
        switch(event.button.button)
        {
            case SDL_BUTTON_LEFT:
                std::cout << "LEFT\n";
                break;
            case SDL_BUTTON_RIGHT:
                std::cout << "RIGHT\n";
                break;
        }
    }
}