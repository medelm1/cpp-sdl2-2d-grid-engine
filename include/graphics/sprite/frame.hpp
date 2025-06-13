#ifndef FRAME_H
#define FRAME_H

#include <iostream>

#include "math/size.hpp"
#include "math/coordinate.hpp"

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

    void setSizeAndDuration(Size size, int coordinate);

    friend std::ostream& operator<<(std::ostream& os, const Frame& frame);
};

#endif