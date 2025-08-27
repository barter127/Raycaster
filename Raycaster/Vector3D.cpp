#define _USE_MATH_DEFINES

#include "Vector3D.h"
#include <stdexcept>
#include <iostream>
#include <cmath>
#include <algorithm>

// Basic operator overloads
Vector3D Vector3D::operator+ (const Vector3D& vector) const
{
    return Vector3D(x + vector.x, y + vector.y, z + vector.z);
}

Vector3D& Vector3D::operator+= (const Vector3D& vector)
{
    x += vector.x;
    y += vector.y;
    z += vector.z;
    return *this;
}

Vector3D Vector3D::operator- (const Vector3D& vector) const
{
    return Vector3D(x - vector.x, y - vector.y, z - vector.z);
}

Vector3D& Vector3D::operator-= (const Vector3D& vector)
{
    x -= vector.x;
    y -= vector.y;
    z -= vector.z;

    return *this;
}

Vector3D Vector3D::operator* (float multiplier) const
{
    return Vector3D(x * multiplier, y * multiplier, z * multiplier);
}

Vector3D& Vector3D::operator*= (float multiplier)
{
    x *= multiplier;
    y *= multiplier;
    z *= multiplier;

    return *this;
}

Vector3D Vector3D::operator/ (float divisor) const
{
    if (divisor == 0)
    {
        std::cout << "Attempted to divide by 0";
    }

    return Vector3D(x / divisor, y / divisor, z / divisor);
}

Vector3D& Vector3D::operator/= (float divisor)
{
    x /= divisor;
    y /= divisor;
    z /= divisor;

    return *this;
}

// Unary -(Vector)
Vector3D Vector3D::operator- () const
{
    return Vector3D(-x, -y, -z);
}

// Outputs dot product of two vectors.
float Vector3D::Dot(Vector3D a, Vector3D b)
{
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

// Outputs cross product of two vectors.
Vector3D Vector3D::Cross(Vector3D a, Vector3D b)
{
    return Vector3D(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}

float Vector3D::Magnitude() const
{
    return sqrt(x * x + y * y + z * z);
}

// Changes instance to normalized Vector.
void Vector3D::Normalize()
{
    float mag = Magnitude();
    if (mag > 0)
    {
        x /= mag;
        y /= mag;
        z /= mag;
    }
}

// Creates a copy of normalized Vector
Vector3D Vector3D::Normalized() const
{
    float mag = Magnitude();
    if (mag > 0)
    {
        return Vector3D(x / mag, y / mag, z / mag);
    }
    return Vector3D();
}

float Vector3D::Distance(Vector3D a, Vector3D b)
{
    float differenceX = pow(a.x - b.x, 2);
    float differenceY = pow(a.y - b.y, 2);
    float differenceZ = pow(a.z - b.z, 2);

    return sqrt(differenceX + differenceY + differenceZ);
}

Vector3D Vector3D::Lerp(Vector3D startPos, Vector3D endPos, float percentComplete)
{
    // Clamp value so it can be used as a percentage multiplier.
    percentComplete = std::clamp(percentComplete, 0.0f, 1.0f);

    Vector3D newPos = startPos + (endPos - startPos) * percentComplete;

    // Use lerp formula to return a point between the two vectors.
    return newPos;
}

Vector3D Vector3D::Coserp(Vector3D startPos, Vector3D endPos, float percentComplete)
{
    float t = 1 - cos(percentComplete * M_PI * 0.5f);

    return Lerp(startPos, endPos, t);
}

void Vector3D::Print() const
{
    std::cout << "[" << x << ", " << y << ", " << z << "]";
}