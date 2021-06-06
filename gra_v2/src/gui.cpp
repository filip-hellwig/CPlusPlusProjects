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
    int flagQueen = 0;


    gameIsRunning = true;

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

    while(gameIsRunning)
    {
        if(currentTurn->isHumanPlayer())
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
                        mouseButtonDown(event, begin_pos, end_pos, b, currentTurn->isWhiteSide(), currentTurn, opponent, additional);
                        break;
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
        } else
        {   
            int alg;
            alg = puppetPawn.minmax(b.getBoard(), currentTurn->getPieceNum(), opponent->getPieceNum(), currentTurn->getAllPieces(),
                            opponent->getAllPieces(), 3, true, begin_pos, end_pos, puppetPos);

            if(alg != -10)
            {
                b.getBoard()[begin_pos.column][begin_pos.row]->makeMove(end_pos, b.getBoard(), flagQueen, opponent->getPieceNum());
                
                std::swap(b.changePiece(end_pos.column, end_pos.row), b.changePiece(begin_pos.column, begin_pos.row));

                if (flagQueen == 1)
                {
                    b.changePiece(end_pos.column, end_pos.row) = std::make_shared<Queen>(end_pos.column, end_pos.row, currentTurn->isWhiteSide());
                    for(int i = 0; i < 8; i++)
                    {
                        if(currentTurn->getAllPieces()[i]->getPosition() == end_pos)
                        {
                            currentTurn->getAllPieces()[i] = b.getBoard()[end_pos.column][end_pos.row];
                        }
                    }
                    flagQueen = 0;
                }
            }

            if (opponent->getPieceNum() == 0
                || opponent->isMoveImpossible(b.getBoard())
                || alg == -10)
            {
                draw(b.getBoard());
                SDL_Color fontColor = {255, 0, 0};
                SDL_Surface* text1 = nullptr;
                if (opponent->isWhiteSide() == true)
                {
                    text1 = TTF_RenderText_Blended(font, "Black", fontColor);
                } else
                {
                    text1 = TTF_RenderText_Blended(font, "White", fontColor);
                }
                SDL_Surface* text2 = TTF_RenderText_Blended(font, "Wins!", fontColor);

                SDL_Rect textRect1 = {400, 400, 200, 100};
                SDL_Rect textRect2 = {400, 500, 200, 100};
                SDL_BlitSurface(text1, nullptr, surface, &textRect1);
                SDL_BlitSurface(text2, nullptr, surface, &textRect2);
                SDL_FreeSurface(text1);
                SDL_FreeSurface(text2);
                SDL_UpdateWindowSurface(window);
                sleep(5);
                
                if(currentTurn->isWhiteSide() == false)
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

            std::swap(currentTurn, opponent);
            draw(b.getBoard());
            begin_pos = control;
            end_pos = control;
            
        }
    }

    SDL_Quit();
    TTF_Quit();
}



void Gui::draw(std::vector<std::vector<std::shared_ptr<Chessman>>>& board)
{
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

void Gui::generateChessman(int column, int row, std::vector<std::vector<std::shared_ptr<Chessman>>>& board)
{
    SDL_Rect imageRect = {132+100*column, 832-100*row, 80, 80};

    if(board[column][row]->isQueen() == true)
    {
        if(board[column][row]->getWhite() == true)
        {
            SDL_BlitSurface(white_queen, nullptr, surface, &imageRect);
        } else
        {
            SDL_BlitSurface(black_queen, nullptr, surface, &imageRect);
        }
    } else
    {
        if(board[column][row]->getWhite() == true)
        {
            SDL_BlitSurface(white_pawn, nullptr, surface, &imageRect);
        } else
        {
            SDL_BlitSurface(black_pawn, nullptr, surface, &imageRect);
        }
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
            case SDL_BUTTON_LEFT:
                if(begin == control)
                {
                    pickButton(event.button.y, event.button.x, begin, end, b, currentTurn, opponent, additional);
                    pickTile(event.button.y, event.button.x, begin);

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
       
                } else if (end == control)
                {
                    pickTile(event.button.y, event.button.x, end);
                    drawPick(end, b.getBoard());
                }
                break;
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

void Gui::returnDown(Position& begin, Position& end, Board& b, int& flagQueen,
                    std::shared_ptr<Player>& currentTurn, std::shared_ptr<Player>& opponent)
{
    Position control(-1,-1);
    
    if(begin != control && end != control)
    {
        if (b.getBoard()[begin.column][begin.row]->makeMove(end, b.getBoard(), flagQueen, opponent->getPieceNum()))
        {
            std::swap(b.changePiece(end.column, end.row), b.changePiece(begin.column, begin.row));

            if (flagQueen == 1)
            {
                b.changePiece(end.column, end.row) = std::make_shared<Queen>(end.column, end.row, currentTurn->isWhiteSide());
                for(int i = 0; i < 8; i++)
                {
                    if(currentTurn->getAllPieces()[i]->getPosition() == end)
                    {
                        currentTurn->getAllPieces()[i] = b.getBoard()[end.column][end.row];
                    }
                }
                flagQueen = 0;
            }

            if (opponent->getPieceNum() == 0
                || opponent->isMoveImpossible(b.getBoard()))
            {
                draw(b.getBoard());
                SDL_Color fontColor = {255, 0, 0};
                SDL_Surface* text1 = nullptr;
                if (opponent->isWhiteSide() == true)
                {
                    text1 = TTF_RenderText_Blended(font, "Black", fontColor);
                } else
                {
                    text1 = TTF_RenderText_Blended(font, "White", fontColor);
                }
                SDL_Surface* text2 = TTF_RenderText_Blended(font, "Wins!", fontColor);

                SDL_Rect textRect1 = {400, 400, 200, 100};
                SDL_Rect textRect2 = {400, 500, 200, 100};
                SDL_BlitSurface(text1, nullptr, surface, &textRect1);
                SDL_BlitSurface(text2, nullptr, surface, &textRect2);
                SDL_FreeSurface(text1);
                SDL_FreeSurface(text2);
                SDL_UpdateWindowSurface(window);
                sleep(5);

                if(currentTurn->isWhiteSide() == false)
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

            std::swap(currentTurn, opponent);
        }
        begin = control;
        end = control;

    }
}

void Gui::pickButton(int y, int x, Position& begin, Position& end, Board& b,
                        std::shared_ptr<Player>& currentTurn, std::shared_ptr<Player>& opponent, std::shared_ptr<Player>& additional)
{
    if (122 <= y && y < 158
        && 886 <= x && x < 1160)
    {
        Position control(-1,-1);

        if(currentTurn->isWhiteSide() == false)
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

    if (222 <= y && y < 258
        && 886 <= x && x < 1260
        && (opponent->isHumanPlayer() == false
        || currentTurn->isHumanPlayer() == false))
    {
        Position control(-1,-1);

        if(currentTurn->isWhiteSide() == false)
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

    if (322 <= y && y < 358
        && 886 <= x && x < 1260
        && currentTurn->isHumanPlayer() == true
        && opponent->isHumanPlayer() == true)
    {
        Position control(-1,-1);

        if(currentTurn->isWhiteSide() == false)
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

void Gui::initBoard()
{
    
    SDL_Rect imageRect = {0, 0, 1280, 1024};
    SDL_BlitSurface(background, nullptr, surface, &imageRect);

    SDL_Rect imageRect2 = {112, 112, 824, 824};
    SDL_BlitSurface(white_bg, nullptr, surface, &imageRect2);

    SDL_Color fontColor = {255, 255, 255};
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

    generateBoard();

    SDL_UpdateWindowSurface(window);
}

void Gui::generateBoard()
{
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