#include "math/offset.hpp"

Offset::Offset()
    :
    m_dx(0), m_dy(0)
{

}

Offset::Offset(int dx, int dy)
    :
    m_dx(dx), m_dy(dy)
{

}

Offset::~Offset()
{

}

int Offset::getDx() const
{
    return m_dx;
}

int Offset::getDy() const
{
    return m_dy;
}

void Offset::setDx(int dx)
{
    m_dx = dx;
}

void Offset::setDy(int dy)
{
    m_dy = dy;
}