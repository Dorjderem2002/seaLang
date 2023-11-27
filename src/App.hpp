#pragma once

#include "6502/BUS.hpp"
#include "6502/CPU.hpp"

class App 
{
public:
    App();
    void start();
    void init();
    void event();
    void update();
    void draw();

    BUS bus;

private:
    bool isRunning = false;
};