#include "coordinate.hpp"

Coordinate::Coordinate()
    :
    m_col(0), m_row(0)
{

}

Coordinate::Coordinate(int col, int row)
    :
    m_col(col), m_row(row)
{

}

Coordinate::~Coordinate()
{

}

int Coordinate::getCol() const
{
    return m_col;
}

int Coordinate::getRow() const
{
    return m_row;
}

void Coordinate::setCol(int col)
{
    m_col = col;
}

void Coordinate::setRow(int row)
{
    m_row = row;
}

std::ostream& operator<<(std::ostream& os, const Coordinate& coord)
{
    os << "(" << coord.m_col << ", " << coord.m_row << ")";
    return os;
}
