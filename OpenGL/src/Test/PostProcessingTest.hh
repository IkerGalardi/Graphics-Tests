#pragma once

#include "Vendor/GLM/glm.hpp"

#include "Test/Test.hh"
#include "Opengl/OpenGL.hh"

class PostProcessingTest : public Test
{
public:
    PostProcessingTest();
    ~PostProcessingTest();


    void Update() override;
    void OnWindowResize(int newX, int newY) override;
    void OnMouseMovement(int mouseX, int mouseY, int deltaX, int deltaY) override;
    void OnKeyPressed(SDL_Scancode keycode) override;
    void OnMouseButtonDown() override;
    void OnMouseButtonUp() override;
private:
    void SetupObjects();
    void SetupPostProcessing();

    void RenderObjects();

    //Rendering objects
    std::unique_ptr<GL::Shader> ObjectShader;
    std::unique_ptr<GL::Texture> ObjectTexture;
    std::unique_ptr<GL::VertexArray> VertexArray;
    std::unique_ptr<GL::Buffer> VertexBuffer;
    std::unique_ptr<GL::Buffer> IndexBuffer;

    // For postprocessing
    std::unique_ptr<GL::Framebuffer> Framebuffer;
    std::shared_ptr<GL::Texture> RenderTexture;
    std::shared_ptr<GL::Texture> DepthTexture;
    std::unique_ptr<GL::VertexArray> PPVertexArray;
    std::unique_ptr<GL::Buffer> PPVertexBuffer;
    std::unique_ptr<GL::Buffer> PPIndexBuffer;
    std::unique_ptr<GL::Shader> PPShader;
    std::unique_ptr<GL::Shader> PlainShader;

    glm::mat4 ProjectionMatrix;
    glm::mat4 TransformationMatrix;
    glm::mat4 ObjectTransform;
    glm::vec3 TexturePosition;

    bool MouseDown;
    int WindowHeight, WindowWidth;
    float AspectRatio;
protected:
};