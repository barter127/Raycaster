#include "Vector2D.h"

#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <algorithm>

// Constructors
Vector2D::Vector2D() : x(0.0f), y(0.0f) {}
Vector2D::Vector2D(float x, float y) : x(x), y(y) {}

// Operator overloads

Vector2D Vector2D::operator+ (const Vector2D& vector) const
{
    return Vector2D(x + vector.x, y + vector.y);
}

Vector2D& Vector2D::operator+= (const Vector2D& vector)
{
    x += vector.x;
    y += vector.y;
    return *this;
}

Vector2D Vector2D::operator- (const Vector2D& vector) const
{
    return Vector2D(x - vector.x, y - vector.y);
}

Vector2D& Vector2D::operator-= (const Vector2D& vector)
{
    x -= vector.x;
    y -= vector.y;
    return *this;
}

Vector2D Vector2D::operator* (float multiplier) const
{
    return Vector2D(x * multiplier, y * multiplier);
}

Vector2D& Vector2D::operator*= (float multiplier)
{
    x *= multiplier;
    y *= multiplier;
    return *this;
}

Vector2D Vector2D::operator/ (float divisor) const
{
    if (divisor == 0)
    {
        throw std::invalid_argument("Attempted to divide Vector2D by 0");
    }
    return Vector2D(x / divisor, y / divisor);
}

Vector2D& Vector2D::operator/= (float divisor)
{
    if (divisor == 0)
    {
        throw std::invalid_argument("Attempted to divide Vector2D by 0");
    }
    x /= divisor;
    y /= divisor;
    return *this;
}

Vector2D Vector2D::operator- () const
{
    return Vector2D(-x, -y);
}

// Static functions

float Vector2D::Dot(Vector2D a, Vector2D b)
{
    return (a.x * b.x) + (a.y * b.y);
}

float Vector2D::Distance(Vector2D a, Vector2D b)
{
    float diffX = a.x - b.x;
    float diffY = a.y - b.y;
    return sqrt(diffX * diffX + diffY * diffY);
}

Vector2D Vector2D::Lerp(Vector2D startPos, Vector2D endPos, float percentComplete)
{
    percentComplete = std::clamp(percentComplete, 0.0f, 1.0f);
    return startPos + (endPos - startPos) * percentComplete;
}

Vector2D Vector2D::Coserp(Vector2D startPos, Vector2D endPos, float percentComplete)
{
    float t = 1 - cos(percentComplete * M_PI * 0.5f);
    return Lerp(startPos, endPos, t);
}

// Member functions

float Vector2D::Magnitude() const
{
    return sqrt(x * x + y * y);
}

void Vector2D::Normalize()
{
    float mag = Magnitude();
    if (mag > 0)
    {
        x /= mag;
        y /= mag;
    }
}

Vector2D Vector2D::Normalized() const
{
    float mag = Magnitude();
    if (mag > 0)
    {
        return Vector2D(x / mag, y / mag);
    }
    return Vector2D();
}

void Vector2D::Print() const
{
    std::cout << "[" << x << ", " << y << "]";
}