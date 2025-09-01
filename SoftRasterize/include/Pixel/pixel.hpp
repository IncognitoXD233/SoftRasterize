#pragma once

#include <SFML\Graphics.hpp>

#include "..\Color\color.hpp"
#include "..\Position\position.hpp"

class Pixel
{
private:
    Color color;
public:
    Pixel() : color{0, 0, 0, 255} {}
    Pixel(sf::Uint8 _R, sf::Uint8 _G, sf::Uint8 _B, sf::Uint8 _A = 255) : color{_R, _G, _B, _A} {}

    void ChangeColor(sf::Uint8 _R, sf::Uint8 _G, sf::Uint8 _B, sf::Uint8 _A = 255);
    // static void InitializePixel(sf::Uint8* _pixelArray, const int _width, const int _height);
    // static void PutPixel(sf::Uint8* _pixelArray, const int _width, const int _height, Position _position, Color _color);
};
