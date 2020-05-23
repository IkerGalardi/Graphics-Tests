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
} quad_t;

typedef struct textured_quad {
    quad_t quad;
    texture_t texture;
} textured_quad_t;


// QUAD FUNCTIONS
quad_t create_quad();
void delete_quad(quad_t quad);

// TEXTURED QUAD FUNCTIONS
textured_quad_t create_textured_quad(const char* textpath);
void delete_textured_quad(textured_quad_t quad);

#endif // TEXTURED_QUAD_H