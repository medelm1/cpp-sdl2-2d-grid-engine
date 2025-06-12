#ifndef SIZE_H
#define SIZE_H

#include <iostream>

class Size
{
private:
    int m_width, m_height;

public:
    Size();
    Size(int width, int height);
    ~Size();

    int getWidth() const;
    int getHeight() const;

    void setWidth(int width);
    void setHeight(int height);

    friend std::ostream& operator<<(std::ostream& os, const Size& size);

};

#endif