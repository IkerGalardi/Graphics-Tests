#pragma once

#include <string>
#include <memory>
#include "Texture.hh"

namespace GL
{
    class Shader
    {
        friend class Texture;
    public:
        Shader(const std::string& vs, const std::string& fs);
        ~Shader();

        void Bind();
        void Unbind();

        static Shader* FromFiles(const std::string& vertexFile, const std::string& fragmentFile);
        
        void SetUniformTexture(const char* name, unsigned int textureSlot);
    private:
        void PrintShaderErrors(unsigned int shaderType, int shaderID);

        unsigned int ProgramID;
    protected:
    };
}