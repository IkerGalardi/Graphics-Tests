#include "post_processing.h"

#include <GL/glew.h>

unsigned int vertex_array;
unsigned int vertex_buffer;
unsigned int index_buffer;

void post_processing_start() {
    // Setup the depth test, blend function and clear color
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);

    // Setup the buffers
    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);

    float vertices[] = 
    {
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
         1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
         1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
        -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
    };
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int indices[] =
    {
        0, 1, 2,
        2, 3, 0
    };
    glGenBuffers(1, &index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindVertexArray(0);
}

void post_processing_update() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindVertexArray(vertex_array);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
}

void post_processing_keyup(int scancode) {

}

void post_processing_keydown(int scancode) {

}

void post_processing_mousemotion(int new_x, int new_y, int x_rel, int y_rel) {

}

void post_processing_mousebuttondown() {

}

void post_processing_mousebuttonup() {

}

void post_processing_end() {

}