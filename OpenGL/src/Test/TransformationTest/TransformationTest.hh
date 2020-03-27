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
    void OnMouseMovement(int mouseX, int mouseY, int deltaX, int deltaY) override;
    void OnKeyPressed(SDL_Scancode keycode) override;
    void OnMouseButtonDown() override;
    void OnMouseButtonUp() override;
private:
    std::unique_ptr<GL::Shader> Shader;
    std::unique_ptr<GL::Texture> Texture;
    std::unique_ptr<GL::VertexArray> VertexArray;
    std::unique_ptr<GL::Buffer> VertexBuffer;
    std::unique_ptr<GL::Buffer> IndexBuffer;

    glm::mat4 ProjectionMatrix;
    glm::mat4 TransformationMatrix;
    glm::mat4 ObjectTransform;
    glm::vec3 TexturePosition;

    bool MouseDown;
    int WindowHeight, WindowWidth;
    float AspectRatio;

    glm::vec4 ScreenToWorld(float mouseX, float mouseY);
    glm::vec2 MouseToNDC(int mouseX, int mouseY);
protected:
};