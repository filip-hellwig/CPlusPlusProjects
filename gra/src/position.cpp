#include "position.hpp"

Position::Position()
{
    column = 0;
    row = 0;
}

Position::Position(int newColumn, int newRow)
{
    row = newRow;
    column = newColumn;
}

Position Position::translateMove(char column, int row)
{
    Position temp;
    temp.row = row-1;
    
    if (column == 'a') { temp.column = 0; }
    else if (column == 'b') { temp.column = 1; }
    else if (column == 'c') { temp.column = 2; }
    else if (column == 'd') { temp.column = 3; }
    else if (column == 'e') { temp.column = 4; }
    else if (column == 'f') { temp.column = 5; }
    else if (column == 'g') { temp.column = 6; }
    else if (column == 'h') { temp.column = 7; }
    else { temp.column = -1; }

    return temp;
}