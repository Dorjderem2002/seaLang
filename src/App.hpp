#pragma once

class App 
{
public:
    App();
    void start();
    void init();
    void event();
    void update();
    void draw();
private:
    bool isRunning = false;
};