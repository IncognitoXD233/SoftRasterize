#pragma once

#include <cmath>
#include <algorithm>

struct Vec3
{
    float x, y, z;
    Vec3(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) : x{_x}, y{_y}, z{_z} {}

    // method
    float Dot(const Vec3& _other) const;
    Vec3 Cross(const Vec3& _other) const;
    float Length() const;
    Vec3 Normalize() const;
    float Distance(const Vec3& _other) const;
    float DistanceSquared(const Vec3& _other) const;
    Vec3 Lerp(const Vec3& _other, float _t) const;

    // tools
    static Vec3 Zero();
    static Vec3 One();
    static Vec3 UnitX();
    static Vec3 UnitY();
    static Vec3 UnitZ();
    bool IsNearZero(float _toLerance = 1e-8f) const;
    Vec3 Abs() const;

    // operator;
    Vec3 operator+(const Vec3& _other) const;
    Vec3 operator-(const Vec3& _other) const;
    Vec3 operator*(float _scalar) const;
    Vec3 operator*(const Vec3& _other) const;
    Vec3 operator/(float _scalar) const;
    Vec3& operator+=(const Vec3& _other);
    Vec3& operator-=(const Vec3& _other);
    Vec3& operator*=(float _scalar);
    Vec3& operator/=(float _scalar);
    bool operator==(const Vec3& _other) const;
    bool operator!=(const Vec3& _other) const;
};
// inlines
inline float Dot(const Vec3& _leftVec, const Vec3& _rightVec) { return _leftVec.Dot(_rightVec); }
inline Vec3 Cross(const Vec3& _leftVec, const Vec3& _rightVec) { return _leftVec.Cross(_rightVec); }
inline Vec3 operator*(float _sacalar, const Vec3& _vec) { return _vec * _sacalar; }
inline Vec3 Reflect(const Vec3& _I, const Vec3& _N) { return _I - _N * (2.0f * _I.Dot(_N)); }
inline float Distance(const Vec3& _leftVec, const Vec3& _rightVec) { return (_leftVec - _rightVec).Length(); }
inline float DistanceSquared(const Vec3& _leftVec, const Vec3& _rightVec)
{
    Vec3 diff = _leftVec - _rightVec;
    return diff.Dot(diff);
}
inline Vec3 Lerp(const Vec3& _leftVec, const Vec3& _rightVec, float _t)
{
    _t = std::clamp(_t, 0.0f, 1.0f);
    return _leftVec + (_rightVec - _leftVec) * _t;
}