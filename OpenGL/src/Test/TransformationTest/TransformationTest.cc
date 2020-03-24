#include "TransformationTest.hh"

#include <iostream>
#include <GL/glew.h>

#include "Vendor/GLM/gtc/matrix_transform.hpp"

TransformationTest::TransformationTest()
    :
    TexturePosition(0.0f, 0.0f ,0.0f),
    ProjectionMatrix(glm::ortho(-1, 1, -1, 1)),
    ObjectTransform(1.0f),
    MouseDown(false),
    WindowHeight(400),
    WindowWidth(400),
    AspectRatio(1)
{
    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Set clear color
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);

    const char* vertexSource = 
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec2 aTexCoord;\n"
    "uniform mat4 transformation;\n"
    "uniform mat4 projection;"
    "out vec2 TexCoord;\n"
    "void main()\n"
    "{\n"
    "   mat4 t = projection * transformation;"
    "   gl_Position = t * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "   TexCoord = aTexCoord;\n"
    "}\0";

    const char* fragmentSource = 
    "#version 330 core\n"
    "in vec2 TexCoord;\n"
    "out vec4 FragColor;\n"
    "uniform sampler2D text;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(TexCoord ,0.0f, 1.0f);\n"
    "   FragColor = texture(text, TexCoord);\n"
    "}\0";

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

    Shader = std::make_unique<GL::Shader>(vertexSource, fragmentSource);

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
}
TransformationTest::~TransformationTest()
{

}
void TransformationTest::Update()
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
void TransformationTest::OnWindowResize(int newX, int newY)
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

void TransformationTest::OnKeyPressed(SDL_Scancode keycode) 
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

void TransformationTest::OnMouseMovement(int deltaX, int deltaY)
{
    if(MouseDown)
    {
        float normalizedDeltaX = (float)deltaX / (float)WindowWidth;
        float normalizedDeltaY = (float)deltaY / (float)WindowHeight;

        TexturePosition.x += normalizedDeltaX * AspectRatio;
        TexturePosition.y += -normalizedDeltaY * AspectRatio;
        
        ObjectTransform = glm::translate(glm::mat4(1.0f), TexturePosition);
        Shader->SetUniformMatrix("transformation", ObjectTransform);
    }
}

void TransformationTest::OnMouseButtonDown()
{
    MouseDown = true;
}

void TransformationTest::OnMouseButtonUp() 
{
    MouseDown = false;
}