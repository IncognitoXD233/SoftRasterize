#pragma once

#include <immintrin.h>

#include "./vec4.hpp"

struct Mat4
{
    union
    {
        alignas(16) float elements[16];
        alignas(16) float mat[4][4];// [row][col]
        __m128 row[4];
    };
    Mat4() { }
    Mat4 Transpose() const;
    Mat4 Inverse() const;// no
    Mat4 FastInverse() const;// no
    float Determinant() const;

    static Mat4 LookAt(const Vec3& _eye, const Vec3& _target, const Vec3& _up);// no
    static Mat4 Identity();
    static Mat4 Translate(float _translateX, float _translateY, float _translateZ);
    static Mat4 Translate(const Vec3& _translateVec);
    static Mat4 Scale(float _scaleX, float _scaleY, float _scaleZ);
    static Mat4 Scale(const Vec3& _scaleVec);
    static Mat4 RotateX(float _rotateX);
    static Mat4 RotateY(float _rotateY);
    static Mat4 RotateZ(float _rotateZ);
    static Mat4 Rotate(float _rotateX, float _rotateY, float _rotateZ);
    static Mat4 Rotate(const Vec3& _rotateVec);

    // tools
    const float* Data() const { return &mat[0][0]; }

    // operators
    Mat4 operator*(const Mat4& _other) const;
    Vec4 operator*(const Vec4& _vec4) const;
    Vec3 operator*(const Vec3& _vec3) const;
    bool operator==(const Mat4& _other) const;
    bool operator!=(const Mat4& _other) const;
};
