#include <vector>


/* Struktura przechowująca pozycję figury na planszy */
struct Position
{
    int column;
    int row;



    /* Konstruktor bezparametryczny przypisuje obu zmiennym 0 */
    Position();

    /* Konstruktor parametryczny, przypisuje odpowiednie zmienne */
    Position(int newColumn, int newRow);

    /* Funkcja zwraca pozycję stworzoną z dwóch zmiennych */
    Position setPostition(int newColumn, int newRow);

    /* Funkcja zwraca wszystkie możliwe pozycje figury na planszy */
    std::vector<Position> allPostitons();

    /* Przeciążenie operatora porównania */
    bool operator==(Position pos);

    /* Przeciążenie operatora nierówności */
    bool operator!=(Position pos);
};

