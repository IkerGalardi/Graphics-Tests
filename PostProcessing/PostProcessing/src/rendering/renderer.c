#include "renderer.h"

#include "opengl/opengl.h"
#include <GL/glew.h>

shader_t texture_shader;

void renderer_initialize(renderer_settings_t settings) {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(settings.clear_color[0], settings.clear_color[1], settings.clear_color[2], settings.clear_color[3]);

    texture_shader = shader_from_files("assets/shaders/simple.vglsl", "assets/shaders/color.fglsl");
}

void renderer_begin_scene(orthographic_camera_t* ortho_cam) {
    // Setup camera
    glUseProgram(texture_shader);
    int location = glGetUniformLocation(texture_shader, "u_view");
    glUniformMatrix4fv(location, 1, GL_FALSE, ortho_cam->view);
}


void renderer_render_quad(quad_t quad) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindVertexArray(quad.vertex_array);

    glUseProgram(texture_shader);
    int loc = glGetUniformLocation(texture_shader, "u_texture");

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, quad.texture);
    glUniform1i(loc, 0);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
}

void rederer_end_scene() {

}