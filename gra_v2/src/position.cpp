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

Position Position::setPostition(int newColumn, int newRow)
{
    Position temp;
    temp.row = newRow;
    temp.column = newColumn;
    return temp;
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

std::vector<Position> Position::allPostitons()
{
    std::vector<Position> all;
    Position pos;
    for(int i = 0; i < 8; i+=2)
    {
        for(int j = 0; j < 8; j+=2)
        {
            all.push_back(pos.setPostition(j, i));
        }
    }
    for(int i = 1; i < 8; i+=2)
    {
        for(int j = 1; j < 8; j+=2)
        {
            all.push_back(pos.setPostition(j, i));
        }
    }
    
    return all;
}

bool Position::operator==(Position pos)
{
    if (column == pos.column
        && row == pos.row)
    {
        return true;
    } else
    {
        return false;
    }
}

bool Position::operator!=(Position pos)
{
    if (column != pos.column
        || row != pos.row)
    {
        return true;
    } else
    {
        return false;
    }
}