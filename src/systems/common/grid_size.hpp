#ifndef GRID_SIZE_H
#define GRID_SIZE_H

class GridSize
{
private:
    int m_cols, m_rows;

public:
    GridSize();
    GridSize(int cols, int rows);
    ~GridSize();

    int getCols() const;
    int getRows() const;

    void setCols(int cols);
    void setRows(int rows);
};

#endif