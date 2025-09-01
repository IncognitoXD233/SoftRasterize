#pragma once

#include <memory>

#include "..\Color\color.hpp"
#include "..\Position\position.hpp"

class Framebuffer
{
private:
    std::unique_ptr<sf::Uint8[]> pixelData;
    const int width, height;
public:
    Framebuffer(int _width, int _height);
    void Clear(const Color& _clearColor = Color(0, 0, 0, 255));
    void SetPixel(Position _position, const Color& _color);
    Color GetPixel(Position _position) const;

    void DrawLine(Position _start, Position _end, const Color& _color);

    const sf::Uint8* GetData() const { return pixelData.get(); }
    int Width() const { return width; }
    int Height() const { return height; }
    int SizeInBytes() const { return width * height * 4; }

    Framebuffer(const Framebuffer&) = delete;
    Framebuffer operator=(const Framebuffer&) = delete;
    ~Framebuffer() = default;

};