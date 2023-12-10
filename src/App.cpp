#include "App.hpp"

#include <iostream>

App::App()
{
}

void App::start()
{
    sf::Clock clock;
    sf::Time deltaTime;
    isRunning = true;
    init();
    while (isRunning && win->isOpen())
    {
        event();
        deltaTime = clock.restart();
        update(deltaTime.asSeconds());
        draw();
    }
}

void App::init()
{
    std::cout << "Successfully initialised" << std::endl;

    win = new sf::RenderWindow(sf::VideoMode(768, 720), "Kimulator - 6502 Emulator");
}

void App::event()
{
    sf::Event e;
    while (win->pollEvent(e))
    {
        if (e.type == sf::Event::Closed)
        {
            isRunning = false;
            win->close();
        }
    }
}

void App::update(float dt)
{
    if (operationTime > 0.0f)
        operationTime -= dt;
    else
    {
        operationTime += (1.0f / 60.0f) - dt;
        do
        {
            bus.clock();
        } while (!bus.ppu.frame_complete);
        bus.ppu.frame_complete = false;
    }
}

void App::draw()
{
    win->clear();

    win->draw(bus.ppu.getScreen());

    win->display();
}