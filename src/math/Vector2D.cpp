#include "math/Vector2D.hpp"

Vector2D::Vector2D()
    : x(0.0f), y(0.0f)
{

}

Vector2D::Vector2D(float xCoord, float yCoord)
    : x(xCoord), y(yCoord)
{

}

Vector2D::Vector2D(const Vector2D& other)
    : x(other.x), y(other.y)
{

}

float Vector2D::getX() const
{
    return x;
}

float Vector2D::getY() const
{
    return y;
}

void Vector2D::setX(float xCoord)
{
    x = xCoord;
}

void Vector2D::setY(float yCoord)
{
    y = yCoord;
}

float Vector2D::length()
{
    return sqrt(x*x + y*y);
}

Vector2D Vector2D::sign()
{
    Vector2D vect;

    if (x > 0) {
        vect.setX(1);
    } else if (x < 0) {
        vect.setX(-1);
    } else {
        vect.setX(0);
    }

    if (y > 0) {
        vect.setY(1);
    } else if (y < 0) {
        vect.setY(-1);
    } else {
        vect.setY(0);
    }

    return vect;
}

Vector2D& Vector2D::normalize()
{
    float len = length();

    if (len > 0) {
        (*this) *= 1 / len;
    }

    return *this;
}

float Vector2D::dot(const Vector2D& other)
{
    return (x * other.x) + (y * other.y);
}

Vector2D Vector2D::project(Axis axis)
{
    if (axis == Axis::X) {
        return {x, 0};

    } else if (axis == Axis::Y) {
        return {0, y};

    }

    return {x, y};
}

Vector2D Vector2D::operator+(const Vector2D& other)
{
    return { x + other.x, y + other.y };
}

Vector2D Vector2D::operator-(const Vector2D& other)
{
    return { x - other.x, y - other.y };
}

Vector2D Vector2D::operator*(const float& scalar)
{
    return { x * scalar, y * scalar };
}

Vector2D Vector2D::operator*(const Vector2D& other)
{
    return { x * other.x, y * other.y };
}

Vector2D Vector2D::operator/(const float& scalar)
{
    return { x / scalar, y / scalar };
}

Vector2D& Vector2D::operator+=(const Vector2D& other)
{
    x += other.x;
    y += other.y;

    return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& other)
{
    x -= other.x;
    y -= other.y;

    return *this;
}

Vector2D& Vector2D::operator/=(const float& scalar)
{
    x /= scalar;
    y /= scalar;

    return *this;
}

Vector2D& Vector2D::operator*=(const float& scalar)
{
    x *= scalar;
    y *= scalar;

    return *this;
}

Vector2D& Vector2D::operator*=(const Vector2D& other)
{
    x *= other.x;
    y *= other.y;

    return *this;
}

bool Vector2D::operator==(const Vector2D& other)
{
    return x == other.x && y == other.y;
}

bool Vector2D::operator!=(const Vector2D& other)
{
    return x != other.x || y != other.y;
}

std::ostream& operator<<(std::ostream& os, const Vector2D& vect)
{
    os << "Vector2D(" << vect.x << ", " << vect.y << ")";
    return os;
}