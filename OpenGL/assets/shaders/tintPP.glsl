#shader vert
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

void main()
{
   mat4 t = transformation * projection;
   gl_Position = aPos;
   TexCoord = aTexCoord;
}

#shader frag
#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D text;

void main()
{
   vec4 textureColor = texture(text, TexCoord);
   FragColor = textureColor * vect4(0.2, 0.0, 0.0, 0.0);
}