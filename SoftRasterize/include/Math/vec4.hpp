#pragma once

#include <cmath>

#include "./vec3.hpp"

struct Vec4
{
    float x, y, z, w;
    Vec4() : x{0.0f}, y{0.0f}, z{0.0f}, w{0.0f} {}
    Vec4(float _x, float _y, float _z, float _w) : x{_x}, y{_y}, z{_z}, w{_w} {}
    Vec4(const Vec3& _vec3, float _w = 1.0f) : x{_vec3.x}, y{_vec3.y}, z{_vec3.z}, w{_w} {}

    // method
    float Dot(const Vec4& _other) const;
    float Length() const;
    float LengthSquared() const;
    Vec4 Normalize() const;
    Vec3 ToVec3() const;
    Vec3 XYZ() const;
    bool IsPoint(float _tolerance = 1e-8f) const;
    bool IsVector(float _tolerance = 1e-8f) const;

    // tools
    static Vec4 Zero();
    static Vec4 Origin();
    static Vec4 UnitX();
    static Vec4 UnitY();
    static Vec4 UnitZ();

    // operator
    Vec4 operator+(const Vec4& _other) const;
    Vec4 operator-(const Vec4& _other) const;
    Vec4 operator*(const Vec4& _other) const;
    Vec4 operator*(float _scalar) const;
    Vec4 operator/(float _scalar) const;
    Vec4& operator+=(const Vec4& _other);
    Vec4& operator-=(const Vec4& _other);
    Vec4& operator*=(float _scalar);
    Vec4& operator/=(float _scalar);
    bool operator==(const Vec4& _other) const;
    bool operator!=(const Vec4& _other) const;
};
// inline
inline float Dot(const Vec4& _leftVec, const Vec4& _rightVec) { return _leftVec.Dot(_rightVec); }
inline Vec4 operator*(float _scalar, const Vec4& _vec) { return _vec * _scalar; }
