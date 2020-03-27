#pragma once

#include <SDL2/SDL.h>

class Test 
{
public:
    Test() = default;
    virtual ~Test() = default;

    virtual void Update() {}
    virtual void OnWindowResize(int newX, int newY) {}
    virtual void OnKeyPressed(SDL_Scancode scancode) {}
    virtual void OnKeyReleased(SDL_Scancode scancode) {}
    virtual void OnMouseButtonDown() {}
    virtual void OnMouseButtonUp() {}
    virtual void OnMouseMovement(int mouseX, int mouseY, int deltaX, int deltaY) {}
private:
protected:
};