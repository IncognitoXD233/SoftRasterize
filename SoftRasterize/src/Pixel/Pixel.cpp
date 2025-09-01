#include "..\..\include\Pixel\pixel.hpp"

void Pixel::ChangeColor(sf::Uint8 _R, sf::Uint8 _G, sf::Uint8 _B, sf::Uint8 _A)
{
    color.R = _R;
    color.G = _G;
    color.B = _B;
    color.A = _A;
}

// void Pixel::InitializePixel(sf::Uint8* _pixelArray, 
//                             const int _width, const int _height)
// {
//     if(_width  > 0 &&
//        _height > 0)
//     {
//         for (int i = 0; i < _width * _height; i++)
//         {
//             _pixelArray[i] = 0;
//             _pixelArray[i + 1] = 0;
//             _pixelArray[i + 2] = 0;
//             _pixelArray[i + 3] = 255;
//         }
//     }
//     else return;
// }

// void Pixel::PutPixel(sf::Uint8* _pixelArray, 
//               const int _width, const int _height, 
//               Position _position, 
//               Color _color)
// {
//     if(_position.x >= 0 && _position.x < _width &&
//        _position.y >= 0 && _position.y < _height)
//     {
//         int index{(_position.y * _width + _position.x) * 4};
//         if (index >= 0 && index < (_width * _height * 4 - 4))
//         {
//             _pixelArray[index] = _color.R;
//             _pixelArray[index + 1] = _color.G;
//             _pixelArray[index + 2] = _color.B;
//             _pixelArray[index + 3] = _color.A;
//         }
//     }
//     else return;
// }