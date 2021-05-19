#include "bishop.hpp"
#include "king.hpp"
#include "knight.hpp"
#include "pawn.hpp"
#include "queen.hpp"
#include "rook.hpp"
#include <iostream>


int main(int argc, char* argv[])
{
    Pawn a(1,6, false);
    char i;
    int j;

    std::cout << "number: \n";
    std::cin >> i;
    std::cin >> j;

    std::cout << a.makeMove(i, j);

    return 0;
}
