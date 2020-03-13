#pragma once

#include <SDL2/SDL.h>

class Test 
{
public:
    Test() = default;
    virtual ~Test() = default;

    virtual void Update() {}
    virtual void OnWindowResize(int newX, int newY) {}
    virtual void OnKeyPressed(SDL_Scancode keycode) {}
private:
protected:
};