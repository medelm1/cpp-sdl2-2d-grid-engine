#ifndef OFFSET_H
#define OFFSET_H

class Offset
{
private:
    int m_dx, m_dy;

public:
    Offset();
    Offset(int dx, int dy);
    ~Offset();

    int getDx() const;
    int getDy() const;

    void setDx(int dx);
    void setDy(int dy);
};

#endif