#pragma once

#include <iostream>
#include <array>
#include <SFML\Graphics.hpp>

#include "..\Framebuffer\framebuffer.hpp"
#include "..\Renderer\renderer.hpp"

class Window
{
private:
    sf::RenderWindow window;
    Framebuffer framebuffer;
    Renderer renderer;
    const int width;
    const int height;

    void HandleEvents();
    void Updata();
    void Render();
    void CreateWindow();

public:
    Window(const int _width, const int _height);

    void Run();
};
