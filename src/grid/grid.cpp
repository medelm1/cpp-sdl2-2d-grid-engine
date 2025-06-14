#include "grid/Grid.hpp"

Grid::Grid(size_t rows, size_t cols, Size cellSize)
    : m_rows(rows), m_cols(cols)
{
    for (size_t index = 0; index < (m_rows * m_cols); index++)
    {
        // Create a new cell at the current grid coordinate
        m_cells[index] = new GridCell(getCoordFromIndex(index, false), cellSize);

        float x = m_cells[index]->getCoord().getX();
        float y = m_cells[index]->getCoord().getY();

        // Link with the left neighbor (if not in the first column)
        if (x-1 >= 0)
        {
            GridCell* leftNeighbor = m_cells[getIndexFromCoord({x-1, y})];

            if (leftNeighbor)
            {
                m_cells[index]->setLeftNeighbor(leftNeighbor);
                leftNeighbor->setRightNeighbor(m_cells[index]);
            }
        }

        // Link with the top neighbor (if not in the first row)
        if (y-1 >= 0)
        {
            GridCell* upNeighbor = m_cells[getIndexFromCoord({x, y-1})];

            if (upNeighbor)
            {
                m_cells[index]->setUpNeighbor(upNeighbor);
                upNeighbor->setDownNeighbor(m_cells[index]);
            }
        }
    }
}

Grid::~Grid()
{
    clean();
}

GridCell* Grid::getCell(size_t index)
{
    validateIndex(index);

    return (m_cells.find(index) != m_cells.end()) ? m_cells[index] : nullptr;
}

GridCell* Grid::getCell(const Vector2D& coord)
{
    size_t index = getIndexFromCoord(coord, true);

    return (m_cells.find(index) != m_cells.end()) ? m_cells[index] : nullptr;
}

void Grid::setCell(size_t index, GridCell* newCell)
{
    if (!newCell) return;

    validateIndex(index);

    auto it = m_cells.find(index);
    if (it != m_cells.end())
    {
        GridCell* oldCell = it->second;

        newCell->setCoord(oldCell->getCoord());
        oldCell->transferNeighborsTo(newCell);

        delete oldCell;

        it->second = newCell;
    }
}

void Grid::replaceCell(size_t index, GridCell* newCell)
{
    replaceCell(index, newCell);
}

void Grid::replaceCell(const Vector2D& coord, GridCell* newCell)
{
    size_t index = getIndexFromCoord(coord, true);
    replaceCell(index, newCell);
}

void Grid::validateIndex(size_t cellIndex)
{
    if (cellIndex >= size())
    {
        throw std::out_of_range("Ivalid cell index");
    }
}

void Grid::validateCoord(const Vector2D& coord)
{
    if (coord.getX() < 0 || coord.getX() >= m_cols || coord.getY() >= m_rows)
    {
        throw std::out_of_range("Invalid coordinate");
    }
}

Vector2D Grid::getCoordFromIndex(size_t index, bool validate)
{
    if (validate) validateIndex(index);

    return {
        (float) (index % m_cols),
        (float) (index / m_cols)
    };
}

size_t Grid::getIndexFromCoord(size_t x, size_t y, bool validate)
{
    if (validate) validateCoord({(float) x, (float) y});

    return y * m_cols + x;
}

size_t Grid::getIndexFromCoord(const Vector2D& coord, bool validate)
{
    if (validate) validateCoord(coord);

    return coord.getY() * m_cols + coord.getX();
}

void Grid::drawLines(SDL_Renderer* renderer)
{
    if (!m_cells.empty())
    {
        Size cellSize = m_cells.at(0)->getSize();

        size_t windowWidth = m_cols * cellSize.getWidth();
        size_t windowHeight = m_rows * cellSize.getHeight();

        SDL_SetRenderDrawColor(renderer, 0x2D, 0x3A, 0x42, 0x40);

        // Draw horizental lines
        for (int y = cellSize.getHeight(); y < windowHeight ; y += cellSize.getHeight()) {
            SDL_RenderDrawLine(renderer, 0, y, windowWidth, y);
        }

        // Draw vertical lines
        for (int x = cellSize.getWidth(); x < windowWidth; x += cellSize.getWidth()) {
            SDL_RenderDrawLine(renderer, x, 0, x, windowHeight);
        }
    }
}

void Grid::forEachCell(std::function<void(size_t, GridCell*)> func)
{
    for (auto& [index, cellptr] : m_cells)
    {
        func(index, cellptr);
    }
}

std::vector<GridCell*> Grid::findCells(std::function<bool(size_t, GridCell*)> predicate)
{
    std::vector<GridCell*> result;

    for (auto& [index, cellptr] : m_cells)
    {
        if (predicate(index, cellptr))
        {
            result.push_back(cellptr);
        }
    }

    return result;
}

Vector2D Grid::normalize(Vector2D pixels)
{
    if (!m_cells.empty())
    {
        Size cellSize = m_cells.at(0)->getSize();

        Vector2D coord = {
            std::trunc(pixels.getX() / cellSize.getWidth()),
            std::trunc(pixels.getY() * cellSize.getHeight())
        };

        return {
            coord.getX() * cellSize.getWidth(),
            coord.getY() * cellSize.getHeight()
        };
    }

    return {-1, -1};
}

void Grid::clean()
{
    for (auto& [_, cell] : m_cells)
    {
        cell->clean();
        delete cell;
    }
    m_cells.clear();
}