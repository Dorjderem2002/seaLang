#include "App.hpp"

#include <iostream>

using namespace std;

App::App()
{

}

void App::start()
{
    isRunning = true;
    init();
    while(isRunning) 
    {
        update();
        draw();
    }
}

void App::init()
{
    cout<<"Successfully initialised"<<endl;
}

void App::event()
{
    
}

void App::update()
{

}

void App::draw()
{

}