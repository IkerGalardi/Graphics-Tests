#ifndef RENDERER_H
#define RENDERER_H

#include "quad.h"

typedef struct renderer_settings {
    float clear_color[4];
} renderer_settings_t;

void renderer_initialize(renderer_settings_t settings);
void renderer_render_quad(quad_t quad);

#endif // RENDERER_H