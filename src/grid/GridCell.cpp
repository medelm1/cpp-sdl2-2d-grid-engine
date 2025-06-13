#include "grid/GridCell.hpp"

GridCell::GridCell(const Vector2D& coord, Size size)
    :
    m_coord(coord),
    m_size(size), 
    m_upNeighbor(nullptr), 
    m_downNeighbor(nullptr), 
    m_leftNeighbor(nullptr), 
    m_rightNeighbor(nullptr)
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

Size GridCell::getSize() const
{
    return m_size;
}

Vector2D GridCell::getPixels()
{
    return {
        std::trunc(m_coord.getX() * m_size.getWidth()),
        std::trunc(m_coord.getY() * m_size.getHeight())
    };
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

bool GridCell::hasNeighbor(Direction direction)
{
    switch (direction)
    {
        case Direction::DIRECTION_UP:
            return m_upNeighbor != nullptr;
        case Direction::DIRECTION_DOWN:
            return m_downNeighbor != nullptr;
        case Direction::DIRECTION_LEFT:
            return m_leftNeighbor != nullptr;
        case Direction::DIRECTION_RIGHT:
            return m_rightNeighbor != nullptr;
        default:
            return false;
    }
}

void GridCell::transferNeighborsTo(GridCell* cellptr)
{
    if (!cellptr) return;

    if (m_upNeighbor)
    {
        cellptr->setUpNeighbor(m_upNeighbor);
        m_upNeighbor->setDownNeighbor(cellptr);
        m_upNeighbor = nullptr;
    }

    if (m_downNeighbor)
    {
        cellptr->setDownNeighbor(m_downNeighbor);
        m_downNeighbor->setUpNeighbor(cellptr);
        m_downNeighbor = nullptr;
    }

    if (m_leftNeighbor)
    {
        cellptr->setLeftNeighbor(m_leftNeighbor);
        m_leftNeighbor->setRightNeighbor(cellptr);
        m_leftNeighbor = nullptr;
    }

    if (m_rightNeighbor)
    {
        cellptr->setRightNeighbor(m_rightNeighbor);
        m_rightNeighbor->setLeftNeighbor(cellptr);
        m_rightNeighbor = nullptr;
    }
}

void GridCell::clean()
{
    m_coord = {0, 0};

    m_upNeighbor = nullptr;
    m_downNeighbor = nullptr;
    m_leftNeighbor = nullptr;
    m_rightNeighbor = nullptr;
}