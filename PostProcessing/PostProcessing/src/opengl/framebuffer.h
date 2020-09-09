#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "texture.h"

typedef struct framebuffer_settings {
    int width, height;
} framebuffer_settings_t;

typedef struct framebuffer {
    framebuffer_settings_t settings;
    unsigned int id;
    texture_t color_texture;
    texture_t depth_texture;
} framebuffer_t;

framebuffer_t create_framebuffer(framebuffer_settings_t settings);
void framebuffer_bind(framebuffer_t* fb);

#endif // FRAMEBUFFER_H