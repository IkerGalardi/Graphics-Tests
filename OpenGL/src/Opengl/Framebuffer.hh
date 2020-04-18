#pragma once

#include "Texture.hh"

#include <memory>

namespace GL
{
    class Framebuffer 
    {
    public:
        Framebuffer();
        ~Framebuffer();

        void AttatchToColor(std::shared_ptr<Texture> texture);
        void AttatchToDepth(std::shared_ptr<Texture> texture);
        void Bind() const;
        void Unbind() const;
    private:
        unsigned int FramebufferID;
    protected:
    };
}