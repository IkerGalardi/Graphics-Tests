#include "BasicTest.hh"

#include "Geometry/Vertex.hh"

#include <iostream>
#include <GL/glew.h>

BasicTest::BasicTest() 
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
    "out vec2 TexCoord;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
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

    shader.reset(new GL::Shader(std::string(vertexSource), std::string(fragmentSource)));
    //shader.reset(GL::Shader::FromFiles(std::string("Shaders/texture.vert.glsl"), std::string("Shaders/texture.frag.glsl")));
    shader->Unbind();

    texture.reset(new GL::Texture("test.jpg"));

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

    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    cvertexBuffer.reset(new GL::Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW));
    cvertexBuffer->SetData(vertices, sizeof(vertices));

    cindexBuffer.reset(new GL::Buffer(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW));
    cindexBuffer->SetData(elements, sizeof(elements));

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)12);
}

BasicTest::~BasicTest() 
{
}

void BasicTest::Update()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glBindVertexArray(vertexArray);

    texture->Bind(0);
    shader->Bind();
    shader->SetUniformTexture("text", 0);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
}

void BasicTest::OnWindowResize(int newX, int newY) 
{
    glViewport(0, 0, newX, newY);
}