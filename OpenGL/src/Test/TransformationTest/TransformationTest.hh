#pragma once

#include "Vendor/GLM/glm.hpp"

#include "Test/Test.hh"
#include "Opengl/OpenGL.hh"

class TransformationTest : public Test
{
public:
    TransformationTest();
    ~TransformationTest();

    void Update() override;
    void OnWindowResize(int newX, int newY) override;
    void OnKeyPressed(SDL_Scancode keycode) override;
private:
    std::unique_ptr<GL::Shader> Shader;
    std::unique_ptr<GL::Texture> Texture;
    std::unique_ptr<GL::VertexArray> VertexArray;
    std::unique_ptr<GL::Buffer> VertexBuffer;
    std::unique_ptr<GL::Buffer> IndexBuffer;

    glm::mat4 ProjectionMatrix;
    glm::mat4 TransformationMatrix;
    glm::vec3 TexturePosition;
protected:
};