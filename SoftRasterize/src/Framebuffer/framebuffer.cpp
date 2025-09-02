#include "..\..\include\Framebuffer\framebuffer.hpp"
#include <iostream>

Framebuffer::Framebuffer(int _width, int _height)
:
width{_width}, height{_height},
pixelData{std::make_unique<sf::Uint8[]>(_width * _height * 4)}
{
    Clear();
}

void Framebuffer::Clear(const Color& _clearColor)
{
    for(int i = 0; i < width * height * 4; i += 4)
    {
        pixelData[i] = _clearColor.R; // R
        pixelData[i + 1] = _clearColor.G; // G
        pixelData[i + 2] = _clearColor.B; // B
        pixelData[i + 3] = _clearColor.A; // A
    }
}

void Framebuffer::SetPixel(Position _position, const Color& _color)
{
    if(_position.x >= 0 && _position.x < width && 
       _position.y >= 0 && _position.y < height)
    {
        int index = (_position.y * width + _position.x) * 4;
        pixelData[index] = _color.R;
        pixelData[index + 1] = _color.G;
        pixelData[index + 2] = _color.B;
        pixelData[index + 3] = _color.A;
    }
    else
    {
        std::cout << "width: " << width << " height: " << height << std::endl;
        std::cout << "x: " << _position.x << " y: " << _position.y << std::endl;
        throw std::runtime_error("[SetPixelError]:Position out of range");
    }
}


Color Framebuffer::GetPixel(Position _position) const
{
    if(_position.x >= 0 && _position.x < width && 
       _position.y >= 0 && _position.y < height)
    {
        int index = (_position.y * width + _position.x) * 4;
        return Color(pixelData[index], pixelData[index + 1], pixelData[index + 2], pixelData[index + 3]);
    }
    else throw std::runtime_error("Position out of range");
}

void Framebuffer::DrawLine(Position _start, Position _end, const Color& _color)
{
    if(_start.x == _end.x) // Vertical Line
    {
        int startY = std::min(_start.y, _end.y);
        int endY = std::max(_start.y, _end.y);
        for(int y = startY; y <= endY; y++)
        {
            SetPixel(Position(_start.x, y), _color);
        }
    }

    if(_start.y == _end.y) // Horizontal Line
    {
        int startX = std::min(_start.x, _end.x);
        int endX = std::max(_start.x, _end.x);
        for(int x = startX; x <= endX; x++)
        {
            SetPixel(Position(x, _start.y), _color);
        }
    }

    if(_start.x != _end.x && 
       _start.y != _end.y) // Diagonal Line
    {
        int x = _start.x;
        int y = _start.y;

        int dx = std::abs(_end.x - _start.x);
        int dy = std::abs(_end.y - _start.y);

        int sx = (_start.x < _end.x) ? 1 : -1;
        int sy = (_start.y < _end.y) ? 1 : -1;

        int err = 2 * dy - dx;

        for(int i = 0; i <= dx; i++)
        {
            SetPixel(Position{x, y}, _color);
            if(err >= 0)
            {
                y += sy;
                err -= 2 * dx;
            }
            err += dy;
            x += sx;
        }
    }
}