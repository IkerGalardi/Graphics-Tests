#pragma once

class Test 
{
public:
    Test() = default;
    virtual ~Test() = default;

    virtual void Update() {}
    virtual void OnWindowResize(int newX, int newY) {}
private:
protected:
};