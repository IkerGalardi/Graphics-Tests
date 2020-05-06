#include "texture.h"

#include "stb_image.h"

texture_t texture_from_file(const char* path, GLenum wrap_type, GLenum resize_filter) {
    texture_t text;
    glGenTextures(1, &text);
    glBindTexture(GL_TEXTURE_2D, text);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, resize_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, resize_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_type);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_type);

    int width, height, channels;
    stbi_set_flip_vertically_on_load(1);
    unsigned char* img_data = stbi_load(path, &width, &height, &channels, STBI_rgb);
    printf("Loaded texture's size : %i x %i x %i\n", width, height, channels);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img_data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(img_data);
    return text;
}

texture_t texture_empty(size_t width, size_t height, GLenum format, GLenum wrap_type, GLenum resize_filter) {
    /// TODO: implement it
}