#include "pawn.hpp"
#include "queen.hpp"
#include "board.hpp"
#include "human.hpp"
#include "computer.hpp"
#include "gui.hpp"

#include <iostream>


int main(int argc, char* argv[])
{
    Gui gui;

    if(!gui.init())
    {
        std::cerr << "Game initialization failed\n";
        return EXIT_FAILURE;
    }

    gui.execGame();

    return EXIT_SUCCESS;
}
