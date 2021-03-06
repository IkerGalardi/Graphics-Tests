#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "post_processing.h"

void GLAPIENTRY message_callback (GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
    char sevirityString[8];
    switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:
            strcpy(sevirityString, "HIGH");
            break;

        case GL_DEBUG_SEVERITY_MEDIUM:
            strcpy(sevirityString, "MEDIUM");
            break;

        case GL_DEBUG_SEVERITY_LOW:
            strcpy(sevirityString, "LOW");
            break;

        case GL_DEBUG_SEVERITY_NOTIFICATION: return;
    }

    fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = %s, message = %s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, sevirityString, message );

    if(severity == GL_DEBUG_SEVERITY_HIGH)
        exit(-1);
}

void setup_opengl_attributes() {
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
}

int main(int argc, char** argv)
{
    printf("%s\n", getcwd(NULL, 0));

    if(SDL_Init(SDL_INIT_EVERYTHING)) {
        fprintf(stderr, "ERROR: error while initializing SDL: %s\n", SDL_GetError());
        exit(-1);
    }

    setup_opengl_attributes();

    SDL_Window* window = SDL_CreateWindow("PostProcessingStack",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          600, 600, 
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(0);

    glewExperimental = true;
    GLenum err = glewInit();
    if(err != GLEW_OK) {
        fprintf(stderr, "ERROR: error while initializing glew.\n");
        exit(-1);
    }

    // Enable debug output
    glViewport(0, 0, 600, 600);
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(message_callback, NULL);

    post_processing_start();

    bool is_running = true;
    SDL_Event event;
    while(is_running) {
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT: {
                    is_running = false;
                } break;

                case SDL_KEYDOWN: {
                    post_processing_keydown(event.key.keysym.scancode);
                } break;

                case SDL_KEYUP: {
                    post_processing_keyup(event.key.keysym.scancode);
                } break;

                case SDL_MOUSEMOTION: {
                    post_processing_mousemotion(event.motion.x, event.motion.y, event.motion.xrel, event.motion.yrel);
                } break;

                case SDL_MOUSEBUTTONDOWN: {
                    post_processing_mousebuttondown(event.button.button);
                } break;

                case SDL_MOUSEBUTTONUP: {
                    post_processing_mousebuttonup(event.button.button);
                } break;
            }
        }

        bool needs_swap = post_processing_update();
        if(needs_swap)
            SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}