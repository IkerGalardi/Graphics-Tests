#include "post_processing.h"

#include <stdio.h>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "opengl/opengl.h"
#include "rendering/renderer.h"
#include "rendering/camera.h"

quad_t textured_quad;
orthographic_camera_t camera;

void post_processing_start() {
    renderer_settings_t settings = {};
    settings.clear_color[1] =  .1f;
    settings.clear_color[2] =  .1f;
    settings.clear_color[3] = 1.0f;
    
    renderer_initialize(settings);

    textured_quad = create_quad("assets/textures/test.jpg");
    camera = create_orthographic_camera((vec2){600, 600}, 0.1f);
}

void post_processing_update() {
    renderer_begin_scene(&camera);
    renderer_render_quad(textured_quad);
    rederer_end_scene();
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