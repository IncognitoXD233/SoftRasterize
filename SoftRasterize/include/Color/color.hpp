#pragma once

#include <cstdint>
#include <SFML\Graphics.hpp>

struct Color
{
    uint32_t value;
    constexpr Color() : value{0xFF000000} {}
    constexpr Color(uint8_t _R, uint8_t _G, uint8_t _B, uint8_t _A = 255)
    :
    value{(_A << 24) | (_B << 16) | (_G << 8) | _R} {}
    explicit constexpr Color(uint32_t _value) : value{_value} {}
    constexpr uint8_t R() const { return (value >> 0) & 0xFF; }
    constexpr uint8_t G() const { return (value >> 8) & 0xFF; }
    constexpr uint8_t B() const { return (value >> 16) & 0xFF; }
    constexpr uint8_t A() const { return (value >> 24) & 0xFF; }
    void SetR(uint8_t _R) { value = (value & 0xFFFFFF00) | _R; }
    void SetG(uint8_t _G) { value = (value & 0xFFFF00FF) | (_G << 8); }
    void SetB(uint8_t _B) { value = (value & 0xFF00FFFF) | (_B << 16); }
    void SetA(uint8_t _A) { value = (value & 0x00FFFFFF) | (_A << 24); }
    operator sf::Color() const
    {
        return sf::Color(
            R(),
            G(),
            B(),
            A()
        );
    }
    Color(const sf::Color& _sfColor) : value{(_sfColor.a << 24) | (_sfColor.b << 16) | (_sfColor.g << 8) | _sfColor.r} {}
};