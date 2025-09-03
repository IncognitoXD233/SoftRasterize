#include "../../include/Math/vec4.hpp"

// methods
#pragma region Method
float Vec4::Dot(const Vec4& _other) const
{
    return x * _other.x + y * _other.y + z * _other.z + w * _other.w;
}
float Vec4::Length() const
{
    return std::sqrt(x * x + y * y + z * z + w * w);
}
float Vec4::LengthSquared() const
{
    return x * x + y * y + z * z + w * w;
}
Vec4 Vec4::Normalize() const
{
    float len = Length();
    if(len < 1e-8f)
    {
        if(IsPoint())
        {
            return Vec4{0.0f, 0.0f, 0.0f, 1.0f};
        }
        else return Vec4{0.0f, 0.0f, 0.0f, 0.0f};
    }
    float invLen = 1.0f / len;
    return Vec4{
        x * invLen,
        y * invLen,
        z * invLen,
        w * invLen
    };
}
Vec3 Vec4::ToVec3() const
{
    if(std::fabs(w) > 1e-8f)
    {
        return Vec3{
            x / w,
            y / w,
            z / w
        };
    }
    return Vec3{
        x,
        y,
        z
    };
}
Vec3 Vec4::XYZ() const
{
    return Vec3{
        x,
        y,
        z
    };
}
bool Vec4::IsPoint(float _tolerance = 1e-8f) const
{
    return std::fabs(w - 1.0f) < _tolerance;
}
bool Vec4::IsVector(float _tolerance = 1e-8f) const
{
    return std::fabs(w) < _tolerance;
}
#pragma endregion

// Tools
#pragma region Tools
Vec4 Vec4::Zero()
{
    return Vec4{0.0f, 0.0f, 0.0f, 0.0f};
}
Vec4 Vec4::Origin()
{
    return Vec4{0.0f, 0.0f, 0.0f, 1.0f};
}
Vec4 Vec4::UnitX()
{
    return Vec4{1.0f, 0.0f, 0.0f, 0.0f};
}
Vec4 Vec4::UnitY()
{
    return Vec4{0.0f, 1.0f, 0.0f, 0.0f};
}
Vec4 Vec4::UnitZ()
{
    return Vec4{0.0f, 0.0f, 1.0f, 0.0f};
}
#pragma endregion

// Operators
#pragma region Operators
Vec4 Vec4::operator+(const Vec4& _other) const
{
    return Vec4{
        x + _other.x,
        y + _other.y,
        z + _other.z,
        w + _other.w
    };
}
Vec4 Vec4::operator-(const Vec4& _other) const
{
    return Vec4{
        x - _other.x,
        y - _other.y,
        z - _other.z,
        w - _other.w
    };
}
Vec4 Vec4::operator*(const Vec4& _other) const
{
    return Vec4{
        x * _other.x,
        y * _other.y,
        z * _other.z,
        w * _other.w
    };
}
Vec4 Vec4::operator*(float _scalar) const
{
    return Vec4{
        x * _scalar,
        y * _scalar,
        z * _scalar,
        w * _scalar
    };
}
Vec4 Vec4::operator/(float _scalar) const
{
    if(std::fabs(_scalar) < 1e-8f)
    {
        return Vec4{0.0f, 0.0f, 0.0f, 0.0f};
    }
    float invScalar = 1.0f / _scalar;
    return Vec4{
        x * invScalar,
        y * invScalar,
        z * invScalar,
        w * invScalar
    };
}
Vec4& Vec4::operator+=(const Vec4& _other)
{
    x += _other.x;
    y += _other.y;
    z += _other.z;
    w += _other.w;
    return *this;
}
Vec4& Vec4::operator-=(const Vec4& _other)
{
    x -= _other.x;
    y -= _other.y;
    z -= _other.z;
    w -= _other.w;
    return *this;
}
Vec4& Vec4::operator*=(float _scalar)
{
    *this *= _scalar;
    return *this;
}
Vec4& Vec4::operator/=(float _scalar)
{
    if(std::fabs(_scalar) < 1e-8f)
    {
        x = y = z = w = 0.0f;
        return *this;
    }
    float invScalar = 1.0f / _scalar; 
    *this *= invScalar;
    return *this;
}
bool Vec4::operator==(const Vec4& _other) const
{
    const float epsilon = 1e-8f;
    // return {
    //     std::fabs(x - _other.x) < epsilon &&
    //     std::fabs(y - _other.y) < epsilon &&
    //     std::fabs(z - _other.z) < epsilon &&
    //     std::fabs(w - _other.w) < epsilon
    // };
    float dx = x - _other.x;
    float dy = y - _other.y;
    float dz = z - _other.z;
    float dw = w - _other.w;
    return (dx * dx + dy * dy + dz * dz + dw * dw) < (epsilon * epsilon);

}
bool Vec4::operator!=(const Vec4& _other) const
{
    return !(*this == _other);
}
#pragma endregion

