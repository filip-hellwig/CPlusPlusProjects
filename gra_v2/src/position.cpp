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