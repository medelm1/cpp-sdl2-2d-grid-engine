#include "math/scale.hpp"

Scale::Scale()
    :
    m_scaleX(1), m_scaleY(1)
{

}

Scale::Scale(float scaleX, float scaleY)
    :
    m_scaleX(scaleX), m_scaleY(scaleY)
{

}

Scale::~Scale()
{

}

float Scale::getScaleX() const
{
    return m_scaleX;
}

float Scale::getScaleY() const
{
    return m_scaleY;
}

void Scale::setScaleX(float scaleX)
{
    m_scaleX = scaleX;
}

void Scale::setScaleY(float scaleY)
{
    m_scaleY = scaleY;
}