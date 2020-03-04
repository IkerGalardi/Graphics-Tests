#include "VertexArray.hh"

#include <GL/glew.h>

static int GetSizeFromGLType(unsigned int type)
{

}

namespace GL
{
        VertexArray::VertexArray()
        {
            glGenVertexArrays(1, &VertexArrayID);
        }

        VertexArray::~VertexArray()
        {
            glDeleteVertexArrays(1, &VertexArrayID);
        }

        void VertexArray::SetAttributes(std::initializer_list<Attribute> attributes)
        {
            unsigned int stride = 0;            
            for(Attribute attrib : attributes)
                stride += GetSizeFromGLType(attrib.Type);
            
            glBindVertexArray(VertexArrayID);
            
            unsigned int i = 0;
            unsigned int offset;
            for(Attribute attrib : attributes) {
                int size = GetSizeFromGLType(attrib.Type);
                glVertexAttribPointer(i, size, attrib.Type, GL_FALSE, stride, (const void*)offset);
                offset += size;
                i++;
            }
        }
}