#pragma once

#include <memory>

#include "Test.hh"
#include "Opengl/Shader.hh"
#include "Opengl/Texture.hh"
#include "Opengl/Buffer.hh"

class BasicTest : public Test 
{
public:
    BasicTest();
    ~BasicTest();

    void Update() override;
    void OnWindowResize(int newX, int newY) override;
private:
    std::shared_ptr<GL::Shader> shader;
    std::shared_ptr<GL::Texture> texture;
    
    std::unique_ptr<GL::Buffer> cvertexBuffer;
    std::unique_ptr<GL::Buffer> cindexBuffer;
    unsigned int vertexArray;
protected:
};