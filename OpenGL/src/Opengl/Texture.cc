#include "Texture.hh"

#include <iostream>
#include <exception>
#include <stdexcept>

#include <GL/glew.h>
#include "Vendor/STBImage/STBImage.h"

namespace GL
{
    Texture::Texture(const char* filepath)
    {
		int width, height, channels;

		stbi_set_flip_vertically_on_load(true);
		unsigned char* image = stbi_load(filepath, &width, &height, 0, STBI_rgb);

		float temp[] = 
		{
    		0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    		1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f
		};

		glGenTextures(1, &TextureID);
		glBindTexture(GL_TEXTURE_2D, TextureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(image);
	}
    
    Texture::~Texture()
    {
        glDeleteTextures(1, &TextureID);
    }
    
    void Texture::Bind(unsigned int textureSlot)
    {
        glActiveTexture(GL_TEXTURE0 + textureSlot);
		glBindTexture(GL_TEXTURE_2D, TextureID);
    }
}
