#include "Shader.hh"

#include <fstream>
#include <iostream> 
#include <sstream>
#include <GL/glew.h>

#define PRINT(X) std::cout << X << std::endl

namespace GL 
{
    static std::string ReadFileString(std::string path)
    {
        std::ifstream file(path);
        std::stringstream stream;
        stream << file.rdbuf();
        return stream.str().append("\0");
    }

    Shader::Shader(const std::string& vs, const std::string& fs) 
    {
        // Create the vertex shader
        const char* vertexSource = vs.c_str();
        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexSource, nullptr);
        glCompileShader(vertexShader);
        PrintShaderErrors(GL_VERTEX_SHADER, vertexShader);
        
        // Create the fragment shader
        const char* fragmentSource = fs.c_str();
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
        glCompileShader(fragmentShader);
        PrintShaderErrors(GL_FRAGMENT_SHADER, fragmentShader);

        // Build the shader program
        ProgramID = glCreateProgram();
        glAttachShader(ProgramID, vertexShader);
        glAttachShader(ProgramID, fragmentShader);
        glLinkProgram(ProgramID);
        glValidateProgram(ProgramID);

        // Cleanup of shaders (program will still work)
        glDetachShader(ProgramID, vertexShader);
        glDeleteShader(vertexShader);
        glDetachShader(ProgramID, fragmentShader);
        glDeleteShader(fragmentShader);
    }

    Shader::~Shader() 
    {
        glDeleteProgram(ProgramID);
    }

    void Shader::Bind()
    {
        glUseProgram(ProgramID);
    }
    void Shader::Unbind()
    {
        glUseProgram(0);
    }

    Shader* Shader::FromFiles(const std::string& vertexPath, const std::string& fragmentPath)
    {
        std::string vertexSource = ReadFileString(vertexPath);
        std::string fragmentSource = ReadFileString(fragmentPath);

        std::cout << vertexSource << std::endl;
        std::cout << fragmentSource << std::endl;

        return new Shader(vertexSource, fragmentSource);
    }

    void Shader::SetUniformTexture(const char* name, unsigned int textureSlot)
    {
        int loc = glGetUniformLocation(ProgramID, name);
        glUniform1i(loc, textureSlot);
    }

    void Shader::PrintShaderErrors(unsigned int shaderType, int shaderID)
    {
        int success;
        char log[512];
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

        if(!success) {
            glGetShaderInfoLog(shaderID, 512, NULL, log);
            if(shaderType == GL_VERTEX_SHADER)
                std::cout << "shader_type -> VERTEX_SHADER\n";
            else if(shaderType == GL_FRAGMENT_SHADER)
                std::cout << "shader_type -> FRAGMENT_SHADER\n";
            else if(shaderType == GL_PROGRAM)
                std::cout << "shader_type -> SHADER_PROGRAM\n";

            std::cout << log << std::endl;
        }
    }
}
