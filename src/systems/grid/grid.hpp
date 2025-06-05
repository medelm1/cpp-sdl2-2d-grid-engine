#ifndef GRID_H
#define GRID_H

#include <unordered_map>
#include <functional>
#include <vector>
#include <SDL.h>

#include "grid_cell.hpp"
#include "../../utils/vector_2d.hpp"

class Grid
{
private:
    size_t m_rows, m_cols, m_cellSize;
    std::unordered_map<size_t, GridCell*> m_cells;

private:
    void validateIndex(size_t index);
    void validateCoord(const Vector2D& coord);

    void setCell(size_t index, GridCell* newCell);

public:
    Grid();
    explicit Grid(size_t rows, size_t cols, size_t cellSize);
    Grid(const Grid& other) = delete;
    ~Grid();

    size_t size() const { return m_cells.size(); };

    size_t getRows() const { return m_rows; }
    size_t getCols() const { return m_cols; }
    size_t getCellSize() const { return m_cellSize; }

    GridCell* getCell(size_t index);
    GridCell* getCell(const Vector2D& coord);

    void replaceCell(size_t index, GridCell* newCell);
    void replaceCell(const Vector2D& coord, GridCell* newCell);

    Vector2D getCoordFromIndex(size_t index, bool validate = true);
    size_t getIndexFromCoord(size_t x, size_t y, bool validate = true);
    size_t getIndexFromCoord(const Vector2D& coord, bool validate = true);

    Vector2D getPixelsFromCoord(Vector2D coord);
    Vector2D getCoordFromPixels(Vector2D pixels);
    Vector2D normalize(Vector2D pixels);

    void forEachCell(std::function<void(size_t, GridCell*)> func);
    std::vector<GridCell*> findCells(std::function<bool(size_t, GridCell*)> predicate);

    void drawLines(SDL_Renderer* renderer);

    void clean();
};

#endif