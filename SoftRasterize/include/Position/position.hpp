#pragma once

struct Position
{
    const int x, y, z;
    Position() : x{0}, y{0}, z{0} {}
    Position(int _x, int _y) : x{_x}, y{_y}, z{0} {}
    Position(int _x, int _y, int _z) : x{_x}, y{_y}, z{_z} {}
    Position operator+(const Position& _other) const
    {
        return Position(x + _other.x, y + _other.y, z + _other.z);
    }
};
