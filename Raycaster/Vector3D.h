#pragma once
#include <string>

#ifndef _VECTOR3D_H
#define _VECTOR3D_H
class Vector3D
{
public:
    float x, y, z;

    // If has parameters, initialize values as parameters. Otherwise, initialize as 0.
    Vector3D(float xInput = 0, float yInput = 0, float zInput = 0)
    {
        x = xInput;
        y = yInput;
        z = zInput;
    }

    Vector3D operator=(const Vector3D& other)
    {
        if (this != &other)
        {
            x = other.x;
            y = other.y;
            z = other.z;
        }
        return *this;
    }

    // ===== Operator Definitions =====

    Vector3D operator+ (const Vector3D&vector) const;
    Vector3D& operator+= (const Vector3D& vector);
    Vector3D operator- (const Vector3D& vector) const;
    Vector3D& operator-= (const Vector3D& vector);
    Vector3D operator* (float multiplier) const;
    Vector3D& operator*= (float multiplier);
    Vector3D operator/ (float divisor) const;
    Vector3D& operator/= (float divisor);
    Vector3D operator- () const;

    // Returns Dot product of two vectors.
    static float Dot(Vector3D a, Vector3D b);

    // Returns Cross product of two vectors.
    static Vector3D Cross(Vector3D a, Vector3D b);

    // Returns the magnitude of the current vector.
    float Magnitude() const;

    // Makes current vector have a magnitude of 1.
    void Normalize();

    // Returns the current vector with a magnitude of 1.
    Vector3D Normalized() const;

    // Returms distance between two points.
    static float Distance(Vector3D a, Vector3D b);

    // Returns linearly interpolated value between startPos and endPos. 
    // percentComplete is clamped between 0 - 1.
    // percentComplete can be used to find a point some fraction along a line between two points.
    static Vector3D Lerp(Vector3D startPos, Vector3D endPos, float percentComplete);
    static Vector3D Coserp(Vector3D startPos, Vector3D endPos, float percentComplete);

    // Print values x, y, and z to the console.
    // Used for debugging.
    void Print() const;
};
#endif
