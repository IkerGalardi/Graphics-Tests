#ifndef SHADER_H
#define SHADER_H

typedef unsigned int shader_t;

shader_t shader_from_files(const char* vertex_filepath, const char* fragment_filepath);

#endif // SHADER_H