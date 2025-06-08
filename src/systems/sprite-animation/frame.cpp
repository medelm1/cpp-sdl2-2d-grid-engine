#include "frame.hpp"

Frame::Frame(Coordinate coordinate)
    :
    m_coordinate(coordinate)
{

}

Frame::~Frame()
{

}

int Frame::getDuration() const
{
    return m_duration;
}

Size Frame::getSize() const
{
    return m_size;
}

Coordinate Frame::getCoordinate() const
{
    return m_coordinate;
}

void Frame::setDuration(int duration)
{
    m_duration = duration;
}

void Frame::setSize(Size size)
{
    m_size = size;
}

void Frame::setCoordinate(Coordinate coordinate)
{
    m_coordinate = coordinate;
}