#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "texture.h"

#define screen_framebuffer  0

typedef struct framebuffer {
    framebuffer_settings_t settings;
    unsigned int id;
    texture_t color_texture;
    texture_t depth_texture;
} framebuffer_t;

typedef struct framebuffer_settings {
    int width, height;
} framebuffer_settings_t;

framebuffer_t create_framebuffer(framebuffer_settings_t settings);

#endif // FRAMEBUFFER_H