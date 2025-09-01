#include "..\..\include\Renderer\renderer.hpp"

Renderer::Renderer() {}

bool Renderer::CreateTexture(const Framebuffer& _framebuffer)
{
    return texture.create(_framebuffer.Width(), _framebuffer.Height());
}

void Renderer::CreateSprite()
{
    sprite.setTexture(texture);
}

void Renderer::UpdataTexture(const Framebuffer& _framebuffer)
{
    texture.update(_framebuffer.GetData());
}

void Renderer::Render(sf::RenderWindow& _window)
{
    _window.draw(sprite);
}

void Renderer::Initialize(const Framebuffer& _framebuffer)
{
    if(!CreateTexture(_framebuffer))
    {
        throw std::runtime_error("Failed to create texture!");
    }
    CreateSprite();
}