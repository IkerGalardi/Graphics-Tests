#include "post_processing.h"

#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "opengl/opengl.h"
#include "rendering/renderer.h"
#include "rendering/camera.h"

quad_t textured_quad;
orthographic_camera_t camera;
bool needs_update = false;

void post_processing_start() {
    renderer_settings_t settings = {};
    glm_vec4((vec3){0.1f,0.1f,0.1f}, 1.0, settings.clear_color);
    
    renderer_initialize(settings);

    textured_quad = create_quad("assets/textures/test.jpg");
    camera = create_orthographic_camera((vec2){600, 600}, 0.1f);
}

void post_processing_update() {
    if(needs_update) {
        renderer_begin_scene(&camera);
        renderer_render_quad(textured_quad);
        renderer_end_scene();
    }
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
    delete_quad(textured_quad);
}