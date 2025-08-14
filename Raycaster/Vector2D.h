#pragma once

#ifndef _VECTOR2D_H
#define _VECTOR2D_H

class Vector2D
{
public:
    float x, y;

    // Constructors
    Vector2D();
    Vector2D(float x, float y);

    // Operator overloads
    Vector2D operator+ (const Vector2D& vector) const;
    Vector2D& operator+= (const Vector2D& vector);

    Vector2D operator- (const Vector2D& vector) const;
    Vector2D& operator-= (const Vector2D& vector);

    Vector2D operator* (float multiplier) const;
    Vector2D& operator*= (float multiplier);

    Vector2D operator/ (float divisor) const;
    Vector2D& operator/= (float divisor);

    Vector2D operator- () const;

    // Static functions
    static float Dot(Vector2D a, Vector2D b);
    static float Distance(Vector2D a, Vector2D b);
    static Vector2D Lerp(Vector2D startPos, Vector2D endPos, float percentComplete);
    static Vector2D Coserp(Vector2D startPos, Vector2D endPos, float percentComplete);

    // Member functions
    float Magnitude() const;
    void Normalize();
    Vector2D Normalized() const;
    void Print() const;
};

#endif // _VECTOR2D_H



