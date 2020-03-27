#include "TransformationTest.hh"

#include <iostream>
#include <GL/glew.h>

#include "Vendor/GLM/gtc/matrix_transform.hpp"

#define PRINTVECTOR2(n, v) std::cout << n << " = (" << v.x << ", " << v.y << ")" << std::endl;

TransformationTest::TransformationTest()
    :
    TexturePosition(0.0f, 0.0f ,0.0f),
    ProjectionMatrix(glm::ortho(-1, 1, -1, 1)),
    ObjectTransform(1.0f),
    MouseDown(false),
    WindowHeight(600),
    WindowWidth(600),
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
    "   mat4 t = transformation * projection;"
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

void TransformationTest::OnMouseMovement(int mouseX, int mouseY, int deltaX, int deltaY)
{
    glm::vec2 n = MouseToNDC(mouseX, mouseY);
    std::cout << n.x << ", " << n.y << std::endl;

    if(MouseDown)
    {
        glm::vec2 normalizedMouse = MouseToNDC(mouseX, mouseY);
        glm::vec4 worldDelta = ScreenToWorld(normalizedMouse.x, normalizedMouse.y);
        TexturePosition = glm::vec3(worldDelta.x * AspectRatio, worldDelta.y, 0.0f);
        
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

glm::vec4 TransformationTest::ScreenToWorld(float mouseX, float mouseY)
{
    glm::vec4 v4 = ProjectionMatrix * glm::vec4(mouseX, mouseY, 0.0f, 0.0f);
    //std::cout << v4.x << ", " << v4.y << ", " << v4.z << ", " << v4.w << std::endl;
    return v4;
}

glm::vec2 TransformationTest::MouseToNDC(int mouseX, int mouseY)
{
    glm::vec2 almostNormalized((float)mouseX / (float)WindowWidth, (float)mouseY / (float)WindowHeight);
    glm::vec2 almostResult = almostNormalized - glm::vec2(0.5f, 0.5f);
    glm::vec2 result(2.0f *almostResult.x, 2.0f * -almostResult.y); 
    return 2.0f * result;
}