#shader vert
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 transformation;
uniform mat4 projection;

out vec2 TexCoord;

void main()
{
   mat4 t = transformation * projection;
   gl_Position = t * vec4(aPos.x, aPos.y, aPos.z, 1.0);
   TexCoord = aTexCoord;
}

#shader frag
#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D text;

void main()
{
   FragColor = vec4(TexCoord ,0.0f, 1.0f);
   FragColor = texture(text, TexCoord);
}