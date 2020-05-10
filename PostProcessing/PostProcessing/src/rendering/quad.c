#include "quad.h"

struct quad create_quad(const char* textpath) {
    quad_t result;

    glGenVertexArrays(1, &result.vertex_array);
    glBindVertexArray(result.vertex_array);

    float vertices[] = 
    {
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
    };
    glGenBuffers(1, &result.vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, result.vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int indices[] =
    {
        0, 1, 2,
        2, 3, 0
    };
    glGenBuffers(1, &result.index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, result.index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    unsigned long stride = 3 * sizeof(float) + 2 * sizeof(float);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (const void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (const void*)(3 * sizeof(float)));

    glBindVertexArray(0);

    result.texture = texture_from_file(textpath, GL_CLAMP_TO_EDGE, GL_LINEAR);

    return result;
}

void delete_quad(quad_t quad) {
    glDeleteVertexArrays(1, &quad.vertex_array);
    glDeleteBuffers(1, &quad.vertex_buffer);
    glDeleteBuffers(1, &quad.index_buffer);
    glDeleteTextures(1, &quad.texture);
}