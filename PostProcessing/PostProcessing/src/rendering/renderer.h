#ifndef RENDERER_H
#define RENDERER_H

#include "quad.h"
#include "camera.h"

typedef struct renderer_settings {
    vec4 clear_color;
} renderer_settings_t;

void renderer_initialize(renderer_settings_t settings);
void renderer_begin_scene(orthographic_camera_t* cam);
void renderer_render_quad(quad_t quad);
void renderer_end_scene();

#endif // RENDERER_H