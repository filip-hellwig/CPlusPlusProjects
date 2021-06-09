#include "gui.hpp"


bool Gui::init()
{
    /* Ustawiamy parametry okna */
    int rendererFlags = SDL_RENDERER_ACCELERATED, windowFlags = 0;
    constexpr auto SCREEN_WIDTH = 1280;
    constexpr auto SCREEN_HEIGHT = 1024;

    if(SDL_Init(SDL_INIT_VIDEO) < 0 || TTF_Init() < 0)
    {
        return false;
    }

    /* Tworzymy okno */
    window = SDL_CreateWindow("Checkers", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
                              windowFlags);

    if(!window)
    {
        return false;
    }

    /* Ustawiamy sposób wyświetlania */
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    /* Ustawiamy powirzchnię do wyświetlania obrazów */
    surface = SDL_GetWindowSurface(window);

    /* Wczysujemy wszystkie powierzchnie potrzebne do wyświetlania */
    font = TTF_OpenFont("../data/font.ttf", 100);
    fontSmall = TTF_OpenFont("../data/font.ttf", 36);
    white_pawn = SDL_LoadBMP("../data/white.bmp");
    black_pawn = SDL_LoadBMP("../data/black.bmp");
    white_queen = SDL_LoadBMP("../data/white_queen.bmp");
    black_queen = SDL_LoadBMP("../data/black_queen.bmp");
    background = SDL_LoadBMP("../data/bc.bmp");
    white_bg = SDL_LoadBMP("../data/white_bg.bmp");
    pale_tile = SDL_LoadBMP("../data/pale_tile.bmp");
    dark_tile = SDL_LoadBMP("../data/dark_tile.bmp");
    pale_tile_pick = SDL_LoadBMP("../data/pale_tile_pick.bmp");
    dark_tile_pick = SDL_LoadBMP("../data/dark_tile_pick.bmp");

    return surface && font && white_pawn && black_pawn && white_queen && fontSmall 
            && black_queen && background && white_bg && pale_tile && dark_tile && pale_tile_pick && dark_tile_pick;
}



void Gui::execGame()
{
    Position begin_pos(-1,-1), end_pos(-1,-1), control(-1,-1), puppetPos;
    Board b;
    std::shared_ptr<Human> p1 = std::make_shared<Human> (true, b.getBoard());
    std::shared_ptr<Human> p2 = std::make_shared<Human> (false, b.getBoard());
    std::shared_ptr<Computer> p3 = std::make_shared<Computer> (false, b.getBoard());
    std::shared_ptr<Player> currentTurn, opponent, additional;
    Pawn puppetPawn(-1,-1,false);
    bool flagQueen = false;

    gameIsRunning = true;

    /* Wybieramy grających graczy */
    if (p1->isWhiteSide()) 
    {
        currentTurn = p1;
        opponent = p2;
    } else 
    {
        currentTurn = p2;
        opponent = p1;
    }
    additional = p3;

    initBoard();
    draw(b.getBoard());

    /* Pętla odpowiadająca za całą grę */
    while(gameIsRunning)
    {
        /* Jeżeli aktualny gracz jest człowiekiem */
        if(currentTurn->isHumanPlayer())
        {
            SDL_Event event;

            /* Pętla oczekuje na kliknięcia myszy lub klawiatury */
            while(SDL_PollEvent(&event))
            {
                switch(event.type)
                {
                    /* Jeżeli przyciśniemy krzyżyk zamknięcia programu to gra wyłącza się */
                    case SDL_QUIT:
                        gameIsRunning = false;
                        break;

                    /* Jeżeli przyciśniemy przycisk myszy */
                    case SDL_MOUSEBUTTONDOWN:
                        mouseButtonDown(event, begin_pos, end_pos, b, currentTurn->isWhiteSide(), currentTurn, opponent, additional);
                        break;

                    /* Jeżeli przyciśniemy przycisk na klawiaturze */
                    case SDL_KEYDOWN:
                        switch(event.key.keysym.sym)
                        {
                            case SDLK_RETURN:
                            returnDown(begin_pos, end_pos, b, flagQueen, currentTurn, opponent);
                            draw(b.getBoard());
                            break;
                        }
                }
            }
        }
        
        /* Tutaj wykonje się ruch komputera */
        else
        {   
            int alg;
            alg = puppetPawn.minmax(b.getBoard(), currentTurn->getPieceNum(), opponent->getPieceNum(), currentTurn->getAllPieces(),
                            opponent->getAllPieces(), 3, true, begin_pos, end_pos, puppetPos);

            /* Jeżeli alg jest równe -10 to oznacza że gracz od samego początku nie mógł się ruszyć */
            if(alg != -10)
            {
                /* Wykonuemy ruch */
                b.getBoard()[begin_pos.column][begin_pos.row]->makeMove(end_pos, b.getBoard(), flagQueen, opponent->getPieceNum());
                
                /* Zamiana figur na planszy */
                std::swap(b.changePiece(end_pos.column, end_pos.row), b.changePiece(begin_pos.column, begin_pos.row));

                /* Zmieniamy pionka na królową */
                if (flagQueen == true)
                {
                    b.changePiece(end_pos.column, end_pos.row) = std::make_shared<Queen>(end_pos.column, end_pos.row, currentTurn->isWhiteSide());
                    for(int i = 0; i < 8; i++)
                    {
                        if(currentTurn->getAllPieces()[i]->getPosition() == end_pos)
                        {
                            currentTurn->getAllPieces()[i] = b.getBoard()[end_pos.column][end_pos.row];
                        }
                    }
                    flagQueen = false;
                }
            }

            /* Sprawdzamy czy ruch nie kończy gry */
            if (opponent->getPieceNum() == 0
                || opponent->isMoveImpossible(b.getBoard())
                || alg == -10)
            {
                /* Aktualizujemy planszę */
                draw(b.getBoard());

                /* Ustawiamy kolor wyświetlania tekstu */
                SDL_Color fontColor = {255, 0, 0};
                SDL_Surface* text1 = nullptr;

                /* W zależności od koloru zwycięscy wyświetlamy różne napisy */
                if (opponent->isWhiteSide())
                {
                    text1 = TTF_RenderText_Blended(font, "Black", fontColor);
                } else
                {
                    text1 = TTF_RenderText_Blended(font, "White", fontColor);
                }
                SDL_Surface* text2 = TTF_RenderText_Blended(font, "Wins!", fontColor);

                /* Wyświetlamy napisy w oknie gry */
                SDL_Rect textRect1 = {400, 400, 200, 100};
                SDL_Rect textRect2 = {400, 500, 200, 100};
                SDL_BlitSurface(text1, nullptr, surface, &textRect1);
                SDL_BlitSurface(text2, nullptr, surface, &textRect2);
                SDL_FreeSurface(text1);
                SDL_FreeSurface(text2);
                SDL_UpdateWindowSurface(window);
                sleep(5);
                
                /* Działania resutujące planszę oraz ustawiające pionki w odpowidnich miejscach.
                    Ustawia różnież gracza białego jako gracza niezaczynającego */
                if(!currentTurn->isWhiteSide())
                {
                    std::swap(currentTurn, opponent);
                }

                b.resetBoard();
                currentTurn->resetPlayer(b.getBoard());
                opponent->resetPlayer(b.getBoard());

                if(currentTurn->isWhiteSide())
                {
                    std::swap(currentTurn, opponent);
                }
            } 

            /* Ustawiamy gracza białego jako zaczynającego.
                Ustawiamy pozycje na control */
            std::swap(currentTurn, opponent);
            draw(b.getBoard());
            begin_pos = control;
            end_pos = control;
            
        }
    }

    SDL_Quit();
    TTF_Quit();
}



void Gui::generateBoard()
{
    /* W pętlach w odpowiednich miejscach rysowane są pytki ciemno brązowe
        lub jasno brązowe, co powoduje stworzenie planszy */
    for(int i = 0; i < 8; i+=2)
    {
        for(int j = 0; j < 8; j+=2)
        {
            SDL_Rect imageRect3 = {122+100*i, 122+100*j, 100, 100};
            SDL_BlitSurface(pale_tile, nullptr, surface, &imageRect3);
        }
    }
    for(int i = 1; i < 8; i+=2)
    {
        for(int j = 1; j < 8; j+=2)
        {
            SDL_Rect imageRect3 = {122+100*i, 122+100*j, 100, 100};
            SDL_BlitSurface(pale_tile, nullptr, surface, &imageRect3);
        }
    }
    for(int i = 0; i < 8; i+=2)
    {
        for(int j = 0; j < 8; j+=2)
        {
            SDL_Rect imageRect3 = {222+100*i, 122+100*j, 100, 100};
            SDL_BlitSurface(dark_tile, nullptr, surface, &imageRect3);
        }
    }
    for(int i = 0; i < 8; i+=2)
    {
        for(int j = 0; j < 8; j+=2)
        {
            SDL_Rect imageRect3 = {122+100*i, 222+100*j, 100, 100};
            SDL_BlitSurface(dark_tile, nullptr, surface, &imageRect3);
        }
    }
}

void Gui::generateChessman(int column, int row, std::vector<std::vector<std::shared_ptr<Chessman>>>& board)
{   
    /* Funkcja w odpowiednim miejscu rysuje odpowiednią figurę.
        Funkcja działa na podstawie reprezentacji planszy klasą Board */
    SDL_Rect imageRect = {132+100*column, 832-100*row, 80, 80};

    if(board[column][row]->isQueen())
    {
        if(board[column][row]->getWhite())
        {
            SDL_BlitSurface(white_queen, nullptr, surface, &imageRect);
        } else
        {
            SDL_BlitSurface(black_queen, nullptr, surface, &imageRect);
        }
    } else
    {
        if(board[column][row]->getWhite())
        {
            SDL_BlitSurface(white_pawn, nullptr, surface, &imageRect);
        } else
        {
            SDL_BlitSurface(black_pawn, nullptr, surface, &imageRect);
        }
    }
}

void Gui::draw(std::vector<std::vector<std::shared_ptr<Chessman>>>& board)
{
    /* Funkcja rysuje całą planszę oraz wszystkie figury na niej,
        później wyświetla wygenerowany obraz. */
    generateBoard();

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if(board[j][i] != nullptr)
            {
                generateChessman(j, i, board);   
            }
        }
    }
    SDL_UpdateWindowSurface(window);

}

void Gui::drawPick(Position& pos, std::vector<std::vector<std::shared_ptr<Chessman>>>& board)
{
    SDL_Rect imageRect3 = {122+100*pos.column, 822-100*pos.row, 100, 100};

    for(int i = -7; i < 8; i++)
    {
        if(122+100*pos.column+200*i == 822-100*pos.row)
        {
            SDL_BlitSurface(pale_tile_pick, nullptr, surface, &imageRect3);
            break;
        } else
        {
            SDL_BlitSurface(dark_tile_pick, nullptr, surface, &imageRect3);
        }
    }

    if(board[pos.column][pos.row] != nullptr)
    {
        generateChessman(pos.column, pos.row, board);
    }

    SDL_UpdateWindowSurface(window);
}

void Gui::unDrawPick(Position& pos, std::vector<std::vector<std::shared_ptr<Chessman>>>& board)
{
    SDL_Rect imageRect3 = {122+100*pos.column, 822-100*pos.row, 100, 100};

    for(int i = -7; i < 8; i++)
    {
        if(122+100*pos.column+200*i == 822-100*pos.row)
        {
            SDL_BlitSurface(pale_tile, nullptr, surface, &imageRect3);
            break;
        } else
        {
            SDL_BlitSurface(dark_tile, nullptr, surface, &imageRect3);
        }
    }

    if(board[pos.column][pos.row] != nullptr)
    {
        generateChessman(pos.column, pos.row, board);
    }

    SDL_UpdateWindowSurface(window);
}

void Gui::drawButton(std::shared_ptr<Player>& opponent)
{
    SDL_Color fontColor = {255, 255, 255};
    SDL_Color fontColor2 = {255, 0, 0};

    if(opponent->isHumanPlayer())
    {
        /* Sygnalizujemy że gra AI */
        SDL_Surface* text4 = TTF_RenderText_Blended(fontSmall, "*", fontColor2);
        SDL_Rect textRect4 = {960, 228, 300, 36};
        SDL_BlitSurface(text4, nullptr, surface, &textRect4);
        SDL_FreeSurface(text4);

        SDL_Surface* text5 = TTF_RenderText_Blended(fontSmall, "*", fontColor);
        SDL_Rect textRect5 = {960, 328, 300, 36};
        SDL_BlitSurface(text5, nullptr, surface, &textRect5);
        SDL_FreeSurface(text5);
    } else
    {
        /* Sygnalizujemy że gra człowiek */
        SDL_Surface* text4 = TTF_RenderText_Blended(fontSmall, "*", fontColor2);
        SDL_Rect textRect4 = {960, 328, 300, 36};
        SDL_BlitSurface(text4, nullptr, surface, &textRect4);
        SDL_FreeSurface(text4);

        SDL_Surface* text5 = TTF_RenderText_Blended(fontSmall, "*", fontColor);
        SDL_Rect textRect5 = {960, 228, 300, 36};
        SDL_BlitSurface(text5, nullptr, surface, &textRect5);
        SDL_FreeSurface(text5);
    }

    SDL_UpdateWindowSurface(window);
}

void Gui::pickTile(int y, int x, Position& pos)
{
    if (122 <= y && y < 922
    && 122 <= x && x < 922)
    {
        if (122 <= y && y < 222) { pos.row = 7; }
        else if (222 <= y && y < 322) { pos.row = 6; }
        else if (322 <= y && y < 422) { pos.row = 5; }
        else if (422 <= y && y < 522) { pos.row = 4; }
        else if (522 <= y && y < 622) { pos.row = 3; }
        else if (622 <= y && y < 722) { pos.row = 2; }
        else if (722 <= y && y < 822) { pos.row = 1; }
        else if (822 <= y && y < 922) { pos.row = 0; }

        if (122 <= x && x < 222) { pos.column = 0; }
        else if (222 <= x && x < 322) { pos.column = 1; }
        else if (322 <= x && x < 422) { pos.column = 2; }
        else if (422 <= x && x < 522) { pos.column = 3; }
        else if (522 <= x && x < 622) { pos.column = 4; }
        else if (622 <= x && x < 722) { pos.column = 5; }
        else if (722 <= x && x < 822) { pos.column = 6; }
        else if (822 <= x && x < 922) { pos.column = 7; }
    }
}

void Gui::pickButton(int y, int x, Position& begin, Position& end, Board& b,
                        std::shared_ptr<Player>& currentTurn, std::shared_ptr<Player>& opponent, std::shared_ptr<Player>& additional)
{
    /* Jeżeli został wybrany przycisk New Game.
        Funkcja zeruje pozycje wybrane przez gracza, ułożenie figur jest resetowane,
        cała plansza też jest resetowana oraz biały jest ustawiany jako gracz zaczynający */
    if (122 <= y && y < 158
        && 886 <= x && x < 1160)
    {
        Position control(-1,-1);

        if(!currentTurn->isWhiteSide())
        {
            std::swap(currentTurn, opponent);
        }

        begin = control;
        end = control;
        
        b.resetBoard();

        currentTurn->resetPlayer(b.getBoard());
        opponent->resetPlayer(b.getBoard());

        draw(b.getBoard());
    }

    /* Jeżeli został wybrany przycisk Play With Human.
        Funkcja zeruje pozycje wybrane przez gracza, ułożenie figur jest resetowane,
        cała plansza też jest resetowana oraz biały jest ustawiany jako gracz zaczynający.
        Dodatkowo przciwnik zamieniamy jest na człowieka */
    if (222 <= y && y < 258
        && 886 <= x && x < 1260
        && (!opponent->isHumanPlayer()
        || !currentTurn->isHumanPlayer()))
    {
        Position control(-1,-1);

        if(!currentTurn->isWhiteSide())
        {
            std::swap(currentTurn, opponent);
        }

        begin = control;
        end = control;

        b.resetBoard();

        currentTurn->resetPlayer(b.getBoard());
        opponent->nullPlayer();
        additional->resetPlayer(b.getBoard());

        std::swap(opponent, additional);

        draw(b.getBoard());
    }

    /* Jeżeli został wybrany przycisk Play With Computer.
        Funkcja zeruje pozycje wybrane przez gracza, ułożenie figur jest resetowane,
        cała plansza też jest resetowana oraz biały jest ustawiany jako gracz zaczynający.
        Dodatkowo przciwnik zamieniamy jest na komputer */
    if (322 <= y && y < 358
        && 886 <= x && x < 1260
        && currentTurn->isHumanPlayer()
        && opponent->isHumanPlayer())
    {
        Position control(-1,-1);

        if(!currentTurn->isWhiteSide())
        {
            std::swap(currentTurn, opponent);
        }

        begin = control;
        end = control;

        b.resetBoard();

        currentTurn->resetPlayer(b.getBoard());
        opponent->nullPlayer();
        additional->resetPlayer(b.getBoard());

        std::swap(opponent, additional);

        draw(b.getBoard());
    }
}

void Gui::mouseButtonDown(SDL_Event& event, Position& begin, Position& end, Board& b,
                            bool white, std::shared_ptr<Player>& currentTurn, std::shared_ptr<Player>& opponent, std::shared_ptr<Player>& additional)
{
    Position control(-1,-1);
    Position check;

    if(event.type == SDL_MOUSEBUTTONDOWN)
    {
        switch(event.button.button)
        {
            /* Lewy przycisk służy do wybierania miejsc w które się ruszamy,
                oraz do wyboru przycisków na planszy. */
            case SDL_BUTTON_LEFT:

                /* Działania wykonywane jeżeli begin nie został jeszcze wybrany */
                if(begin == control)
                {
                    pickButton(event.button.y, event.button.x, begin, end, b, currentTurn, opponent, additional);
                    drawButton(opponent);

                    pickTile(event.button.y, event.button.x, begin);

                    /* Sprawdzamy czy begin jest poprawną figurą */
                    if(begin != control)
                    {
                        if(b.getBoard()[begin.column][begin.row] == nullptr)
                        {
                            begin = control;    
                        } else if(b.getBoard()[begin.column][begin.row]->getWhite() != white)
                        {
                            begin = control;
                        } else
                        {
                            drawPick(begin, b.getBoard());
                        }
                    }
       
                } 
                
                /* Działania wykonywane jeżeli begin został wybrany, a end nie */
                else if (end == control)
                {
                    pickTile(event.button.y, event.button.x, end);

                    if(end != control)
                    {
                        drawPick(end, b.getBoard());
                    }
                }

                break;

            /* Prawy przycisk służy do zmiany wybranej pozycji początkowej
                lub końcowej */
            case SDL_BUTTON_RIGHT:
                pickTile(event.button.y, event.button.x, check);

                if(check == begin)
                {
                    unDrawPick(begin, b.getBoard());
                    begin = control;
                } else if(check == end)
                {
                    unDrawPick(end, b.getBoard());
                    end = control;
                }

                break;
        }
    }
}

void Gui::returnDown(Position& begin, Position& end, Board& b, bool& flagQueen,
                    std::shared_ptr<Player>& currentTurn, std::shared_ptr<Player>& opponent)
{
    Position control(-1,-1);
    
    /* Sprawdzamy czy obie pozycje zostały już wybrane */
    if(begin != control && end != control)
    {
        /* Sprawdzamy czy ruch jest możliwy oraz wykonujemy go */
        if (b.getBoard()[begin.column][begin.row]->makeMove(end, b.getBoard(), flagQueen, opponent->getPieceNum()))
        {
            /* Zamieniamy figury na planszy */
            std::swap(b.changePiece(end.column, end.row), b.changePiece(begin.column, begin.row));

            /* Zamieniamy pionek na królową */
            if (flagQueen == true)
            {
                b.changePiece(end.column, end.row) = std::make_shared<Queen>(end.column, end.row, currentTurn->isWhiteSide());
                for(int i = 0; i < 8; i++)
                {
                    if(currentTurn->getAllPieces()[i]->getPosition() == end)
                    {
                        currentTurn->getAllPieces()[i] = b.getBoard()[end.column][end.row];
                    }
                }
                flagQueen = false;
            }

            /* Sprawdzamy czy gra się kończy */
            if (opponent->getPieceNum() == 0
                || opponent->isMoveImpossible(b.getBoard()))
            {
                /* Aktualizujemy planszę */
                draw(b.getBoard());

                /* Ustawiamy kolor wyświetlania tekstu */
                SDL_Color fontColor = {255, 0, 0};
                SDL_Surface* text1 = nullptr;

                /* W zależności od koloru zwycięscy wyświetlamy różne napisy */
                if (opponent->isWhiteSide())
                {
                    text1 = TTF_RenderText_Blended(font, "Black", fontColor);
                } else
                {
                    text1 = TTF_RenderText_Blended(font, "White", fontColor);
                }
                SDL_Surface* text2 = TTF_RenderText_Blended(font, "Wins!", fontColor);

                /* Wyświetlamy napisy w oknie gry */
                SDL_Rect textRect1 = {400, 400, 200, 100};
                SDL_Rect textRect2 = {400, 500, 200, 100};
                SDL_BlitSurface(text1, nullptr, surface, &textRect1);
                SDL_BlitSurface(text2, nullptr, surface, &textRect2);
                SDL_FreeSurface(text1);
                SDL_FreeSurface(text2);
                SDL_UpdateWindowSurface(window);
                sleep(5);
                
                /* Działania resutujące planszę oraz ustawiające pionki w odpowidnich miejscach.
                    Ustawia różnież gracza białego jako gracza niezaczynającego */
                if(!currentTurn->isWhiteSide())
                {
                    std::swap(currentTurn, opponent);
                }

                b.resetBoard();
                currentTurn->resetPlayer(b.getBoard());
                opponent->resetPlayer(b.getBoard());

                if(currentTurn->isWhiteSide())
                {
                    std::swap(currentTurn, opponent);
                }
            } 

            /* Ustawiamy białego jako gracza zaczynającego */
            std::swap(currentTurn, opponent);
        }
        /* Zerujemy wektory pozycji */
        begin = control;
        end = control;
    }
}

void Gui::initBoard()
{
    /* Wyświetlamy tło w oknie */
    SDL_Rect imageRect = {0, 0, 1280, 1024};
    SDL_BlitSurface(background, nullptr, surface, &imageRect);

    /* Wyświetlamy białe tło dla planszy */
    SDL_Rect imageRect2 = {112, 112, 824, 824};
    SDL_BlitSurface(white_bg, nullptr, surface, &imageRect2);

    /* Wyświetlamy wszystkie potrzebne przyciski */
    SDL_Color fontColor = {255, 255, 255};
    SDL_Color fontColor2 = {255, 0, 0};
    SDL_Surface* text = TTF_RenderText_Blended(fontSmall, "New game", fontColor);
    SDL_Rect textRect = {986, 122, 200, 36};
    SDL_BlitSurface(text, nullptr, surface, &textRect);
    SDL_FreeSurface(text);

    SDL_Surface* text2 = TTF_RenderText_Blended(fontSmall, "Play with human", fontColor);
    SDL_Rect textRect2 = {986, 222, 300, 36};
    SDL_BlitSurface(text2, nullptr, surface, &textRect2);
    SDL_FreeSurface(text2);

    SDL_Surface* text3 = TTF_RenderText_Blended(fontSmall, "Play with AI", fontColor);
    SDL_Rect textRect3 = {986, 322, 300, 36};
    SDL_BlitSurface(text3, nullptr, surface, &textRect3);
    SDL_FreeSurface(text3);

    SDL_Surface* text4 = TTF_RenderText_Blended(fontSmall, "*", fontColor2);
    SDL_Rect textRect4 = {960, 228, 300, 36};
    SDL_BlitSurface(text4, nullptr, surface, &textRect4);
    SDL_FreeSurface(text4);

    SDL_Surface* text5 = TTF_RenderText_Blended(fontSmall, "*", fontColor);
    SDL_Rect textRect5 = {960, 328, 300, 36};
    SDL_BlitSurface(text5, nullptr, surface, &textRect5);
    SDL_FreeSurface(text5);

    /* Wyświetlamy planszę */
    generateBoard();

    SDL_UpdateWindowSurface(window);
}

