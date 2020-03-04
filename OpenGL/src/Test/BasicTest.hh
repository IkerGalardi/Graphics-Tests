#pragma once

#include <memory>

#include "Test.hh"
#include "Opengl/Shader.hh"
#include "Opengl/Texture.hh"
#include "Opengl/Buffer.hh"
#include "Opengl/VertexArray.hh"

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
    
    std::unique_ptr<GL::Buffer> VertexBuffer;
    std::unique_ptr<GL::Buffer> IndexBuffer;
    std::unique_ptr<GL::VertexArray> VertexArray;
protected:
};