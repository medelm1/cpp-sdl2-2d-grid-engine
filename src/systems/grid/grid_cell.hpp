#ifndef GRID_CELL_H
#define GRID_CELL_H

#include <vector>
#include <algorithm>
#include <functional>
#include <random>
#include <iterator>

#include "../../utils/vector_2d.hpp"
#include "../common/direction.hpp"
#include "../common/size.hpp"

#include "../../entities/game_object.hpp"

class GridCell
{
private:
    Vector2D m_coord;

    Size m_size;

    GridCell* m_upNeighbor;
    GridCell* m_downNeighbor;
    GridCell* m_leftNeighbor;
    GridCell* m_rightNeighbor;

public:
    GridCell(const Vector2D& coord, Size size);
    ~GridCell();

    Vector2D getCoord() const { return m_coord; }
    void setCoord(const Vector2D& coord) { m_coord = coord; }
    Vector2D getPixels();

    int getRow() const { return m_coord.getX(); }
    int getCol() const { return m_coord.getY(); }

    Size getSize() const;

    void setUpNeighbor(GridCell* upNeighbor) { m_upNeighbor = upNeighbor; }
    void setDownNeighbor(GridCell* downNeighbor) { m_downNeighbor = downNeighbor; }
    void setLeftNeighbor(GridCell* leftNeighbor) { m_leftNeighbor = leftNeighbor; }
    void setRightNeighbor(GridCell* rightNeighbor) { m_rightNeighbor = rightNeighbor; }

    GridCell* getUpNeighbor() const { return m_upNeighbor; }
    GridCell* getDownNeighbor() const { return m_downNeighbor; }
    GridCell* getLeftNeighbor() const { return m_leftNeighbor; }
    GridCell* getRightNeighbor() const { return m_rightNeighbor; }

    bool hasNeighbor(Direction direction);

    GridCell* getNextNeighbor(Direction direction) const;

    void transferNeighborsTo(GridCell* cellptr);

    bool operator==(const GridCell& other);
    bool operator!=(const GridCell& other);

    void clean();
};

#endif