#include "Framebuffer.hh"

#include <GL/glew.h>

namespace GL
{
    Framebuffer::Framebuffer()
    {
        glGenFramebuffers(1, &FramebufferID);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    Framebuffer::~Framebuffer()
    {
        glDeleteFramebuffers(1, &FramebufferID);
    }

    void Framebuffer::AttatchToColor(const Texture& texture)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, FramebufferID);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.TextureID, 0);
        glBindFramebuffer(GL_FRAMEBUFFER, FramebufferID);
    }

    void Framebuffer::Bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, FramebufferID);
    }

    void Framebuffer::Unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}