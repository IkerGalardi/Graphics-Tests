#include "post_processing.h"

#include <stdio.h>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "opengl/opengl.h"
#include "rendering/renderer.h"
#include "rendering/camera.h"

textured_quad_t textured_quad;
orthographic_camera_t camera;
bool needs_render = false;

void post_processing_start() {
    renderer_settings_t settings = {};
    glm_vec4((vec3){0.1f,0.1f,0.1f}, 1.0, settings.clear_color);
    
    renderer_initialize(settings);

    textured_quad = create_textured_quad("assets/textures/test.jpg");
    camera = create_orthographic_camera((vec2){600, 600}, 1.0f);

    needs_render = true;
}

bool post_processing_update() {
    if(needs_render) {
        renderer_begin_scene(&camera, screen_framebuffer);
        renderer_draw_textured_quad(textured_quad);
        renderer_end_scene();

        needs_render = false;
        return true;
    }

    return false;
}

void post_processing_keyup(int scancode) {
    printf("%i key was released\n", scancode);
}

void post_processing_keydown(int scancode) {
    printf("%i key was pressed\n", scancode);
}

void post_processing_mousemotion(int new_x, int new_y, int x_rel, int y_rel) {

}

void post_processing_mousebuttondown(int button) {

}

void post_processing_mousebuttonup(int button) {

}

void post_processing_end() {
    delete_textured_quad(textured_quad);
}