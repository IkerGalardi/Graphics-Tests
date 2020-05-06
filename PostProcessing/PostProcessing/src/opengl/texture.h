#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>

typedef unsigned int texture_t;

texture_t texture_from_file(const char* path, GLenum wrap_type, GLenum resize_filter);
texture_t texture_empty(size_t width, size_t height, GLenum format, GLenum wrap_type, GLenum resize_filter);

#endif // TEXTURE_H