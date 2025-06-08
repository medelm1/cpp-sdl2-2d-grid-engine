#ifndef FRAME_H
#define FRAME_H

#include "../common/size.hpp"
#include "../common/coordinate.hpp"

class Frame
{
private:
    int             m_duration;
    Size            m_size;
    Coordinate      m_coordinate;


public:
    Frame();
    Frame(Coordinate coordinate);

    ~Frame();

    int getDuration() const;
    Size getSize() const;
    Coordinate getCoordinate() const;

    void setDuration(int duration);
    void setSize(Size size);
    void setCoordinate(Coordinate coordinate);
};

#endif