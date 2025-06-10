#ifndef GRID_CELL_H
#define GRID_CELL_H

#include <vector>
#include <algorithm>
#include <functional>
#include <random>
#include <iterator>

#include "../../utils/vector_2d.hpp"
#include "../common/direction.hpp"

#include "../../entities/game_object.hpp"

class GridCell
{
private:
    Vector2D m_coord;

    GridCell* m_upNeighbor;
    GridCell* m_downNeighbor;
    GridCell* m_leftNeighbor;
    GridCell* m_rightNeighbor;

    std::vector<GameObject*> m_gameObjects;

public:
    GridCell();
    GridCell(const Vector2D& coord);
    ~GridCell();

    Vector2D getCoord() const { return m_coord; }
    void setCoord(const Vector2D& coord) { m_coord = coord; }

    int getRow() const { return m_coord.getX(); }
    int getCol() const { return m_coord.getY(); }

    void setUpNeighbor(GridCell* upNeighbor) { m_upNeighbor = upNeighbor; }
    void setDownNeighbor(GridCell* downNeighbor) { m_downNeighbor = downNeighbor; }
    void setLeftNeighbor(GridCell* leftNeighbor) { m_leftNeighbor = leftNeighbor; }
    void setRightNeighbor(GridCell* rightNeighbor) { m_rightNeighbor = rightNeighbor; }

    GridCell* getUpNeighbor() const { return m_upNeighbor; }
    GridCell* getDownNeighbor() const { return m_downNeighbor; }
    GridCell* getLeftNeighbor() const { return m_leftNeighbor; }
    GridCell* getRightNeighbor() const { return m_rightNeighbor; }

    GridCell* getNextNeighbor(Direction direction) const;

    void transferNeighborsTo(GridCell* cellptr);

    bool operator==(const GridCell& other);
    bool operator!=(const GridCell& other);

    void clean();

    void addGameObject(GameObject* gameObject);

    void updateGameObjects();
    void renderGameObjects(SDL_Renderer* renderer);
};

#endif