#ifndef VECTOR_2D_H
#define VECTOR_2D_H

#include <math.h>
#include <ostream>

class Vector2D
{

private:
    float x;
    float y;

public:
    enum class Axis { X, Y };

    Vector2D();
    Vector2D(float xCoord, float yCoord);
    Vector2D(const Vector2D& other);

    float getX() const;
    float getY() const;

    void setX(float xCoord);
    void setY(float yCoord);

    float length();
    Vector2D sign();

    Vector2D& normalize();

    float dot(const Vector2D& other);
    Vector2D project(Axis axis);

    Vector2D operator+(const Vector2D& other);
    Vector2D operator-(const Vector2D& other);
    Vector2D operator*(const float& scalar);
    Vector2D operator*(const Vector2D& other);
    Vector2D operator/(const float& scalar);
    Vector2D& operator+=(const Vector2D& other);
    Vector2D& operator-=(const Vector2D& other);
    Vector2D& operator/=(const float& scalar);
    Vector2D& operator*=(const float& scalar);
    Vector2D& operator*=(const Vector2D& other);
    bool operator==(const Vector2D& other);
    bool operator!=(const Vector2D& other);
    friend std::ostream& operator<<(std::ostream& os, const Vector2D& vect);

};

#endif