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

void Frame::setSizeAndDuration(Size size, int duration)
{
    m_size = size;
    m_duration = duration;
}

std::ostream& operator<<(std::ostream& os, const Frame& frame)
{
    os << "Frame("
       << "Coordinate: " << frame.getCoordinate() << ", "
       << "Size: " << frame.getSize() << ", "
       << "Duration: " << frame.getDuration() << " ms)";
    return os;
}