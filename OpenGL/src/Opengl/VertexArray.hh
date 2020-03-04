#pragma once

#include <vector>
#include <initializer_list>

#include "Buffer.hh"

namespace GL
{
    struct Attribute
    {
        unsigned int Count;
        unsigned int Type;
        unsigned int Offset;
    };

    class VertexArray
    {
    public:
        VertexArray();
        ~VertexArray();

        void SetAttributes(std::initializer_list<Attribute> attributes); 
    private:
        unsigned int VertexArrayID;
    protected:
    };
}