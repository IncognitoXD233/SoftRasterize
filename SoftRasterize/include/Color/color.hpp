#pragma once

#include <SFML\Graphics.hpp>

struct Color
{
    sf::Uint8 R, G, B, A;
    constexpr Color()
    :
    R{0}, G{0}, B{0}, A{255} {}
    constexpr Color(sf::Uint8 _R, sf::Uint8 _G, sf::Uint8 _B, sf::Uint8 _A = 255)
    :
    R{_R}, G{_G}, B{_B}, A{_A} {}
    // constexpr Color(const Color& _color) = default;

    Color(const Color&) = default;

    operator sf::Color() const
    {
        return {R, G, B, A};
    }
};
