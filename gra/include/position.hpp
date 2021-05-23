struct Position
{
    int row;
    int column;

    Position();
    Position(int newColumn, int newRow);
    Position translateMove(char column, int row);
};
