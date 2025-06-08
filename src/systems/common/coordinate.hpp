#ifndef COORDINATE_H
#define COORDINATE_H

#include <iostream>

class Coordinate
{
private:
    int m_col, m_row;

public:
    Coordinate();
    Coordinate(int col, int row);
    ~Coordinate();

    int getCol() const;
    int getRow() const;

    void setCol(int col);
    void setRow(int row);

    friend std::ostream& operator<<(std::ostream& os, const Coordinate& coord);

};

#endif