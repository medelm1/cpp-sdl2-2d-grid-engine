#include "grid/GridSize.hpp"

GridSize::GridSize()
    :
    m_cols(0), m_rows(0)
{

}

GridSize::GridSize(int cols, int rows)
    :
    m_cols(cols), m_rows(rows)
{

}

GridSize::~GridSize()
{

}

int GridSize::getCols() const
{
    return m_cols;
}

int GridSize::getRows() const
{
    return m_rows;
}

void GridSize::setCols(int cols)
{
    m_cols = cols;
}

void GridSize::setRows(int rows)
{
    m_rows = rows;
}