#include "PostProcessingTest.hh"

#include <iostream>
#include <GL/glew.h>

#include "Vendor/GLM/gtc/matrix_transform.hpp"

#define PRINTVECTOR2(n, v) std::cout << n << " = (" << v.x << ", " << v.y << ")" << std::endl;

PostProcessingTest::PostProcessingTest()
    :
    TexturePosition(0.0f, 0.0f ,0.0f),
    ProjectionMatrix(glm::ortho(-1, 1, -1, 1)),
    ObjectTransform(1.0f),
    MouseDown(false),
    WindowHeight(600),
    WindowWidth(600),
    AspectRatio(600 / 600)
{
    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Set clear color
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);

    float vertices[] = 
    {
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
         1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
         1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
        -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
    };

    unsigned int elements[] =
    {
        0, 1, 2,
        2, 3, 0
    };

    Shader.reset(GL::Shader::FromFile("assets/shaders/textured.glsl"));

    VertexArray = std::make_unique<GL::VertexArray>();
    VertexArray->Bind();

    VertexBuffer = std::make_unique<GL::Buffer>(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    VertexBuffer->SetData(vertices, sizeof(vertices));

    IndexBuffer = std::make_unique<GL::Buffer>(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
    IndexBuffer->SetData(elements, sizeof(elements));

    VertexArray->SetAttributes({{3, GL_FLOAT}, {2, GL_FLOAT}});

    Texture = std::make_unique<GL::Texture>("test.jpg");

    ObjectTransform = glm::translate(glm::mat4(1.0f), TexturePosition);
    Shader->Bind();
    Shader->SetUniformMatrix("transformation", ObjectTransform);
    Shader->SetUniformMatrix("projection", ProjectionMatrix);

    glGenFramebuffers(1, &fbo);
    glBindBuffer(GL_FRAMEBUFFER, fbo);
}
PostProcessingTest::~PostProcessingTest()
{
    
}

void PostProcessingTest::Render()
{
    // Create transformation matrix and send to shader
    Shader->Bind();
    Shader->SetUniformMatrix("transformation", ObjectTransform);
    
    // Clear screen and render
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    VertexArray->Bind();
    Texture->Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void PostProcessingTest::Update()
{

}
void PostProcessingTest::OnWindowResize(int newX, int newY)
{
    // Local variables
    WindowHeight = newY;
    WindowWidth = newX;

    // Framebuffer resizing
    glViewport(0, 0, newX, newY);

    // Projection matrix update
    AspectRatio = (float)newX / (float)newY;
    ProjectionMatrix = glm::ortho(-AspectRatio, AspectRatio, -1.0f, 1.0f);
    Shader->SetUniformMatrix("projection", ProjectionMatrix);
}

void PostProcessingTest::OnKeyPressed(SDL_Scancode keycode) 
{
    float speed = .1f;

    if(keycode == SDL_SCANCODE_W)
    {
        TexturePosition.y += speed;
    }
    else if(keycode == SDL_SCANCODE_S)
    {
        TexturePosition.y -= speed;
    }
    else if(keycode == SDL_SCANCODE_A)
    {
        TexturePosition.x -= speed;
    }
    else if(keycode == SDL_SCANCODE_D)
    {
        TexturePosition.x += speed;
    }
}

void PostProcessingTest::OnMouseMovement(int mouseX, int mouseY, int deltaX, int deltaY)
{
}

void PostProcessingTest::OnMouseButtonDown()
{
}

void PostProcessingTest::OnMouseButtonUp() 
{
}