#ifndef QUAD_H
#define QUAD_H

#include "opengl/opengl.h"

enum {
    VERTEX_BUFFER = 0,
    INDEX_BUFFER = 1
};

typedef struct quad {
    vertex_array_t vertex_array;
    buffer_t vertex_buffer;
    buffer_t index_buffer;
    texture_t texture;
} quad_t;

quad_t create_quad(const char* textpath);
void delete_quad(quad_t quad);

#endif // TEXTURED_QUAD_H