#include "..\..\include\Window\window.hpp"
#include <cmath>

Window::Window(int _width, int _height)
:
width(_width), height(_height),
framebuffer{_width, _height}
{
    CreateWindow();
}

void Window::CreateWindow()
{
    window.create(sf::VideoMode(width, height), "SoftRasterize Window");
    if(!window.isOpen())
    {
        throw std::runtime_error("Window creation failed!");
    }
    renderer.Initialize(framebuffer);
}

void Window::Run()
{
    while(window.isOpen())
    {
        HandleEvents();
        Updata();
        Render();
    }
}

void Window::HandleEvents()
{
    sf::Event event;
    while(window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            window.close();
        }
    }
}

void Window::Updata()
{
    // framebuffer.SetPixel(Position{100, 100}, Color{255, 0, 0, 255});
    // framebuffer.SetPixel(Position{200, 100}, Color{255, 0, 0, 255});
    // framebuffer.SetPixel(Position{150, 200}, Color{255, 0, 0, 255});
    framebuffer.DrawLine(Position{150, 150}, Position{50, 150}, Color{0, 0, 255, 255});
    framebuffer.DrawLine(Position{100, 100}, Position{150, 150}, Color{255, 0, 0, 255});
    framebuffer.DrawLine(Position{100, 100}, Position{50, 150}, Color{0, 255, 0, 255});
}

void Window::Render()
{
    window.clear();
    renderer.UpdataTexture(framebuffer);
    renderer.Render(window);
    window.display();
}