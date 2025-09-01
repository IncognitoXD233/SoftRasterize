#pragma once

#include <SFML\Graphics.hpp>
#include <array>

#include "..\Framebuffer\framebuffer.hpp"

class Renderer
{
private:
    sf::Texture texture;
    sf::Sprite sprite;

    bool CreateTexture(const Framebuffer& _framebuffer);
    void CreateSprite();
public:
    Renderer();

    void Initialize(const Framebuffer& _framebuffer);
    void UpdataTexture(const Framebuffer& _framebuffer);
    void Render(sf::RenderWindow& _window);
};