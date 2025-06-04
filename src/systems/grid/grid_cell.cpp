#include "grid_cell.hpp"

GridCell::GridCell()
    :
    m_coord({0, 0}), m_upNeighbor(nullptr), m_downNeighbor(nullptr), m_leftNeighbor(nullptr), m_rightNeighbor(nullptr)
{

}

GridCell::GridCell(const Vector2D& coord)
    :
    m_coord(coord), m_upNeighbor(nullptr), m_downNeighbor(nullptr), m_leftNeighbor(nullptr), m_rightNeighbor(nullptr)
{

}

GridCell::~GridCell()
{
    clean();
}

bool GridCell::operator==(const GridCell& other)
{
    return m_coord == other.m_coord;
}

bool GridCell::operator!=(const GridCell& other)
{
    return m_coord != other.m_coord;
}

GridCell* GridCell::getNextNeighbor(Direction direction) const
{
    switch (direction)
    {
        case Direction::DIRECTION_UP:
            return getUpNeighbor();

        case Direction::DIRECTION_DOWN:
            return getDownNeighbor();

        case Direction::DIRECTION_LEFT:
            return getLeftNeighbor();

        case Direction::DIRECTION_RIGHT:
            return getRightNeighbor();

        default:
            return nullptr;
    }
}

void GridCell::clean()
{
    delete m_upNeighbor;
    delete m_downNeighbor;
    delete m_leftNeighbor;
    delete m_rightNeighbor;

    m_upNeighbor = nullptr;
    m_downNeighbor = nullptr;
    m_leftNeighbor = nullptr;
    m_rightNeighbor = nullptr;
}