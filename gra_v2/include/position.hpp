struct Position
{
    int row;
    int column;

    Position();
    Position(int newColumn, int newRow);
    Position setPostition(int newColumn, int newRow);
    Position translateMove(char column, int row);
    bool operator==(Position pos);
    bool operator!=(Position pos);
};
