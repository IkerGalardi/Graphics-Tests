#pragma once

#include "Texture.hh"

namespace GL
{
    class Framebuffer 
    {
    public:
        Framebuffer();
        ~Framebuffer();

        void AttatchToColor(const Texture& texture);
        void Bind();
        void Unbind();
    private:
        unsigned int FramebufferID;
    protected:
    };
}