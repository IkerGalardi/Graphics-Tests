#pragma once

#include "Vendor/GLM/glm.hpp"

#include "Test/Test.hh"
#include "Opengl/OpenGL.hh"

class PostProcessingTest : public Test
{
public:
    PostProcessingTest();
    ~PostProcessingTest();

    void Render();

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

    unsigned int fbo;

    glm::mat4 ProjectionMatrix;
    glm::mat4 TransformationMatrix;
    glm::mat4 ObjectTransform;
    glm::vec3 TexturePosition;

    bool MouseDown;
    int WindowHeight, WindowWidth;
    float AspectRatio;
protected:
};