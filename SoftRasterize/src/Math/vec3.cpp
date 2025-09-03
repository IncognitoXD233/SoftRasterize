#include "../../include/Math/vec3.hpp"

// Methods
#pragma region Methods
float Vec3::Dot(const Vec3& _other) const
{
    return x * _other.x + y * _other.y + z * _other.z;
}

Vec3 Vec3::Cross(const Vec3& _other) const
{
    return Vec3{
        y * _other.z - z * _other.y,
        z * _other.x - x * _other.z,
        x * _other.y - y * _other.x
    };
}

float Vec3::Length() const
{
    return std::sqrt(x * x + y * y + z * z);
}

Vec3 Vec3::Normalize() const
{
    float len = Length();
    if(len < 1e-8f)
    {
        return Vec3{0.0f, 0.0f, 0.0f};
    }
    float invLen = 1.0f / len;
    return Vec3{
        x * invLen,
        y * invLen,
        z * invLen
    };
}

float Vec3::Distance(const Vec3& _other) const
{
    return (*this - _other).Length();
}

float Vec3::DistanceSquared(const Vec3& _other) const
{
    Vec3 diff = *this - _other;
    return (
        diff.x * diff.x +
        diff.y * diff.y +
        diff.z * diff.z
    );
}

Vec3 Vec3::Lerp(const Vec3& _other, float _t) const
{
    _t = std::clamp(_t, 0.0f, 1.0f);
    return *this + (_other - *this) * _t;
}

#pragma endregion

// Tools
#pragma region Tools
Vec3 Vec3::Zero() 
{ 
    return Vec3(0.0f, 0.0f, 0.0f); 
}
Vec3 Vec3::One() 
{ 
    return Vec3(1.0f, 1.0f, 1.0f); 
}
Vec3 Vec3::UnitX() 
{ 
    return Vec3(1.0f, 0.0f, 0.0f); 
}
Vec3 Vec3::UnitY() 
{ 
    return Vec3(0.0f, 1.0f, 0.0f); 
}
Vec3 Vec3::UnitZ() 
{ 
    return Vec3(0.0f, 0.0f, 1.0f); 
}
bool Vec3::IsNearZero(float _toLerance = 1e-8f) const
{
    return {
        (std::fabs(x) < _toLerance) && 
        (std::fabs(y) < _toLerance) && 
        (std::fabs(z) < _toLerance)
    };
}

Vec3 Vec3::Abs() const
{
    return Vec3{
        std::abs(x),
        std::abs(y),
        std::abs(z)
    };
}

#pragma endregion

// Operators
#pragma region Operators
Vec3 Vec3::operator+(const Vec3& _other) const
{
    return Vec3{
        x + _other.x,
        y + _other.y,
        z + _other.z
    };  
}
Vec3 Vec3::operator-(const Vec3& _other) const
{
    return Vec3{
        x - _other.x,
        y - _other.y,
        z - _other.z
    };  
}
Vec3 Vec3::operator*(float _scalar) const
{
    return Vec3{
        x * _scalar,
        y * _scalar,
        z * _scalar
    };  
}
Vec3 Vec3::operator*(const Vec3& _other) const
{
    return Vec3{
        x * _other.x,
        y * _other.y,
        z * _other.z
    };
}

Vec3 Vec3::operator/(float _scalar) const
{
    if(std::fabs(_scalar) < 1e-8f)
    {
        return Vec3{0.0f, 0.0f, 0.0f};
    }
    float invScalar = 1.0f / _scalar;
    return Vec3{
        x * invScalar,
        y * invScalar,
        z * invScalar
    };  
}
Vec3& Vec3::operator+=(const Vec3& _other)
{
    x += _other.x;
    y += _other.y;
    z += _other.z;
    return *this;
}
Vec3& Vec3::operator-=(const Vec3& _other)
{
    x -= _other.x;
    y -= _other.y;
    z -= _other.z;
    return *this;
}
Vec3& Vec3::operator*=(float _scalar)
{
    x *= _scalar;
    y *= _scalar;
    z *= _scalar;
    return *this;
}
Vec3& Vec3::operator/=(float _scalar)
{
    if(std::fabs(_scalar) < 1e-8f)
    {
        x = y = z = 0.0f;
        return *this;
    }
    float invScalar = 1.0f / _scalar;
    x *= invScalar;
    y *= invScalar;
    z *= invScalar;
    return *this;
}

bool Vec3::operator==(const Vec3& _other) const
{
    return (
        std::fabs(x - _other.x) < 1e-8f &&
        std::fabs(y - _other.y) < 1e-8f &&
        std::fabs(z - _other.z) < 1e-8f
    );
}
bool Vec3::operator!=(const Vec3& _other) const
{
    return !(*this == _other);
}

#pragma endregion
