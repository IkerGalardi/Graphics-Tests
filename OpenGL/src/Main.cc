#include <iostream>
#include <stdio.h>
#include <memory>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "Test/Test.hh"
#include "Test/BasicTest.hh"
#include "Test/TransformationTest.hh"
#include "Test/PostProcessingTest.hh"

#define WINDOW_SIZE 600, 600

void GLAPIENTRY MessageCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* message,
                 const void* userParam )
{

    std::string severityString = "HEHE";
    switch (severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:
            severityString = "HIGH";
            break;

        case GL_DEBUG_SEVERITY_MEDIUM:
            severityString = "MEDIUM";
            break;

        case GL_DEBUG_SEVERITY_LOW:
            severityString = "LOW";
            break;

        case GL_DEBUG_SEVERITY_NOTIFICATION: return;
        
        default:
            severityString = "lel";
            break;
    }

    fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = %s, message = %s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, severityString.c_str(), message );

    if(severity == GL_DEBUG_SEVERITY_HIGH)
        std::exit(-1);
}

int main(int argc, char** argv) 
{
    try
    {
        if(SDL_Init(SDL_INIT_EVERYTHING))
        {
            std::cerr << "Error initializing SDL:" << SDL_GetError() << std::endl;
            std::exit(-1);
        }

        // Setup of OpenGL attributes for SDL
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,32);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,16);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

        // Create the window and context
        SDL_Window* window = SDL_CreateWindow("Titulaso",
                                           SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                           WINDOW_SIZE,
                                           SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
        if(window == NULL) {
            std::cerr << "SDL window creation failed: " << SDL_GetError() << std::endl;
            std::exit(-1);
        }
        SDL_GLContext context = SDL_GL_CreateContext(window);
        SDL_GL_MakeCurrent(window, context);
        SDL_GL_SetSwapInterval(0);

        // Initialize opengl
        glewExperimental = true;
        GLenum err = glewInit();
        if(err != GLEW_OK)
        {
            std::cerr << "GLEW initialization failed: " << err << std::endl;
            std::exit(-1);
        }
        glViewport(0, 0, WINDOW_SIZE);
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(MessageCallback, nullptr);

        std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
        std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
        
        std::unique_ptr<Test> test;
        test.reset(new PostProcessingTest());

        SDL_Event event;
        bool running = true;
        while (running) {
            // Event handling code
            if(SDL_PollEvent(&event)) {
                switch(event.type) {
                    case SDL_QUIT:
                        running = false;
                        break;

                    case SDL_WINDOWEVENT:
                        switch (event.window.event)
                        {
                            case SDL_WINDOWEVENT_RESIZED:
                                test->OnWindowResize(event.window.data1, event.window.data2);
                        }
                        break;

                    case SDL_KEYDOWN:
                        test->OnKeyPressed(event.key.keysym.scancode);
                        break;

                    case SDL_KEYUP:
                        test->OnKeyReleased(event.key.keysym.scancode);
                        break;

                    case SDL_MOUSEMOTION:
                        test->OnMouseMovement(event.motion.x, event.motion.y,
                                              event.motion.xrel, event.motion.yrel);
                        break;

                    case SDL_MOUSEBUTTONDOWN:
                        test->OnMouseButtonDown();
                        break;
                    
                    case SDL_MOUSEBUTTONUP:
                        test->OnMouseButtonUp();
                        break;
                }
            }

            // Other stuff
            test->Update();
            SDL_GL_SwapWindow(window);
        }

        test.release();

        SDL_GL_DeleteContext(context);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    
}