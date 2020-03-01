#pragma once

namespace GL
{
    class Texture
    {
    public:
        Texture(const char* filepath);
        ~Texture();

        void Bind(unsigned int textureSlot = 0);
    private:
        unsigned int TextureID;
    protected:
    };
}