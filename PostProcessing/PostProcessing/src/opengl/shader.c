#include "shader.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

#include <GL/glew.h>

#define PRINT(x) printf("%s\n", x)

char* read_file(const char* filepath) {
    FILE* file = fopen(filepath, "r");
    if(file == NULL)
        return NULL;

    fseek(file, 0, SEEK_END);
    unsigned int file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* file_contents = malloc(sizeof(char) * (file_size + 1));
    int nread = 0;
    while((nread = fread(file_contents, 1, file_size, file)) > 0);
    
    return file_contents;
}

unsigned int create_and_compile_shader(GLenum shader_type, const char* shader_source) {
    unsigned int shader_id = glCreateShader(shader_type);
    glShaderSource(shader_id, 1, &shader_source, NULL);
    glCompileShader(shader_id);

    return shader_id;
}

shader_t shader_from_files(const char* vertex_filepath, const char* fragment_filepath) {
    char* vertex_shader_source = read_file(vertex_filepath);
    char* fragment_shader_source = read_file(fragment_filepath);

    unsigned int vertex_shader = create_and_compile_shader(GL_VERTEX_SHADER, vertex_shader_source);
    unsigned int fragment_shader = create_and_compile_shader(GL_FRAGMENT_SHADER, fragment_shader_source);
    free(vertex_shader_source);
    free(fragment_shader_source);

    shader_t shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);
    glValidateProgram(shader_program);

    glDetachShader(shader_program, fragment_shader);
    glDetachShader(shader_program, vertex_shader);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    glUseProgram(0);
    
    return shader_program;
}