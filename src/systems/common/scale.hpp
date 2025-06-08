#ifndef SCALE_H
#define SCALE_H

class Scale
{
private:
    float m_scaleX, m_scaleY;

public:
    Scale();
    Scale(float scaleX, float scaleY);
    ~Scale();

    float getScaleX() const;
    float getScaleY() const;

    void setScaleX(float scaleX);
    void setScaleY(float scaleY);
};

#endif