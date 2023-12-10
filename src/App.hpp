#pragma once

#include "6502/BUS.hpp"
#include "6502/CPU.hpp"
#include "6502/Cartridge.hpp"

#include <SFML/Graphics.hpp>

class App 
{
public:
    App();
    void start();
    void init();
    void event();
    void update(float dt);
    void draw();

private:
    sf::RenderWindow *win;
    BUS bus;
    std::shared_ptr<Cartridge> cart;
    bool isRunning = false;

    float operationTime = 0;
};