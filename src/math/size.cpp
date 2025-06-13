#include "math/size.hpp"

Size::Size()
    :
    m_width(0), m_height(0)
{

}

Size::Size(int width, int height)
    :
    m_width(width), m_height(height)
{

}

Size::~Size()
{

}

int Size::getWidth() const
{
    return m_width;
}

int Size::getHeight() const
{
    return m_height;
}

void Size::setWidth(int width)
{
    m_width = width;
}

void Size::setHeight(int height)
{
    m_height = height;
}

std::ostream& operator<<(std::ostream& os, const Size& size)
{
    os << "(" << size.m_width << " x " << size.m_height << ")";
    return os;
}
