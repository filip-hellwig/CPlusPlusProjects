#ifndef CHESSMAN_HPP_
#define CHESSMAN_HPP_

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <memory>
#include "position.hpp"

class Chessman
{
    protected:
        Position position; 
        bool existance;
        bool white;
    
    public:
        virtual bool makeMove(int column, int row, std::vector<std::vector<std::shared_ptr<Chessman>>> board) = 0;
        bool checkMoveValidity(int column, int row);
        virtual std::string name() = 0;


        Chessman(int column, int row, bool isWhite)
        {
            Position newPosition(column, row);
            position = newPosition;
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

        bool getWhite() { return white; }
        bool getExistance() { return existance; }
};


#endif