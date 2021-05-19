#ifndef CHESSMAN_HPP_
#define CHESSMAN_HPP_

#include <stdlib.h>
#include <iostream>

struct Position
{
    int row;
    int column;
};


class Chessman
{
    protected:
        Position position; 
        bool existance;
        bool white;
    
    public:
        virtual bool makeMove(char column, int row) = 0;
        bool checkMoveValidity(int column, int row);


        Chessman(int column, int row, bool isWhite)
        {
            position.column = column;
            position.row = row;
            existance = true;
            white = isWhite;
        }        

        bool checkIndexValidity(int column, int row)
        {
            if (row > 7 || row < 0)
            {
                return false;
            }
            if (column > 7 || row < 0)
            {
                return false;
            }
            return true;
        }

        Position translateMove(char column, int row)
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
};


#endif